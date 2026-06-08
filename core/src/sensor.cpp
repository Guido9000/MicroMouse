#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "sensor.h"

adc_oneshot_unit_handle_t IRSensor::adc1_handle = nullptr;
bool IRSensor::adc_initialized = false;
SemaphoreHandle_t IRSensor::adcMutex_ = xSemaphoreCreateMutex();

Sensor::~Sensor() {}

// Trampolines
void UsSensor::sUSSensorTask(void* instance) {      // sUSSensorTask public entry point that FreeRTOS calls from outside
    static_cast<UsSensor*>(instance)->sonarTask();  // sonarTask is the real loop, an internal private function
}
void IRSensor::sIRSensorTask(void* instance) {
    static_cast<IRSensor*>(instance)->irTask();
}


bool UsSensor::ussensor_setup()
{
    // Setup pins
    gpio_reset_pin((gpio_num_t)p_echoPin);
    gpio_set_direction((gpio_num_t)p_echoPin, GPIO_MODE_INPUT);
    gpio_reset_pin((gpio_num_t)p_trigPin);
    gpio_set_direction((gpio_num_t)p_trigPin, GPIO_MODE_OUTPUT);

    gpio_set_level((gpio_num_t)p_trigPin, 0);

    // register echo_isr on echo pin with rise and fall
    // pass this as argument so that echo_isr knows which object update
    gpio_set_intr_type((gpio_num_t)p_echoPin, GPIO_INTR_ANYEDGE);
    gpio_isr_handler_add((gpio_num_t)p_echoPin, echo_isr, this);

    LOG_VERBOSE("US sensor", "Online")
    return true;
}


float UsSensor::read() const
{
    return 0.0f;
}


bool UsSensor::theresWall() const
{
    if(read() < MAX_WALL_DIST){return true;}
    else{return false;}
}


void UsSensor::sonarTask()
{
    // Configuration ping and empty spurious notifications linked to setup
    ulTaskNotifyTake(pdTRUE, portMAX_DELAY);
    xTaskNotifyStateClear(NULL);

    for (;;)
    {
        // Wait ping from master
        ulTaskNotifyTake(pdTRUE, portMAX_DELAY);

        // Trigger
        gpio_set_level((gpio_num_t)p_trigPin, 0);
        esp_rom_delay_us(4);    // clean the signal

        gpio_set_level((gpio_num_t)p_trigPin, 1);
        esp_rom_delay_us(10);
        gpio_set_level((gpio_num_t)p_trigPin, 0);

        // check for the rise of echo
        if(!ulTaskNotifyTake(pdTRUE, pdMS_TO_TICKS(120))) {
            sendReading(-1.0);  // timeout
            continue;
        }
        // check for the fall of echo
        if(!ulTaskNotifyTake(pdTRUE, pdMS_TO_TICKS(120))) {
            sendReading(-2.0);  // timeout
            continue;
        }

        float distance = (echo_end_time_ - echo_start_time_) / 58.0f;
        sendReading(distance);
    }
}


// Add this function in the IRAM (Instruction RAM, faster then Flash)
// Use IRAM for ISR (Interrupt Service Routine)
// when pin echo goes HIGH, the hardware calls echo_isr automatically
void IRAM_ATTR UsSensor::echo_isr(void* instance)
{
    UsSensor* self = static_cast<UsSensor*>(instance);

    if (gpio_get_level((gpio_num_t)self->p_echoPin))
    {
        self->echo_start_time_ = esp_timer_get_time();

        // Notify sonar timeout on echo rise
        BaseType_t hpw = pdFALSE;
        if (self->classTaskHandle_ != NULL) {
            vTaskNotifyGiveFromISR(self->classTaskHandle_, &hpw);
            portYIELD_FROM_ISR(hpw);
        }
    }
    else
    {
        self->echo_end_time_ = esp_timer_get_time();

        // Notify sonar timeout on echo fall
        // Higher Priority-task Woken
        BaseType_t hpw = pdFALSE;
        // wake up Sonar task if waiting, equivalent to ulTaskNotifyTake(...) in task
        vTaskNotifyGiveFromISR(self->classTaskHandle_, &hpw);
        portYIELD_FROM_ISR(hpw);
    }
}


bool IRSensor::irsensor_setup()
{
    // Configure analog reading pin
    if (!adc_initialized)
    {
        // Configure handle
        adc_oneshot_unit_init_cfg_t init_config1 = {
            .unit_id = ADC_UNIT_1,
            .clk_src = ADC_RTC_CLK_SRC_DEFAULT,
            .ulp_mode = ADC_ULP_MODE_DISABLE,
        };

        ESP_ERROR_CHECK(
            adc_oneshot_new_unit(&init_config1, &adc1_handle)
        );

        adc_initialized = true;
    }

    adc_oneshot_chan_cfg_t config = {
        .atten = ADC_ATTEN_DB_12,
        .bitwidth = ADC_BITWIDTH_DEFAULT,
    };
    ESP_ERROR_CHECK(adc_oneshot_config_channel(adc1_handle, p_adc_channel, &config));

    LOG_VERBOSE("IR sensor", "Online")
    return true;
}


bool IRSensor::theresWall() const
{
    if(read() < MAX_WALL_DIST){return true;}
    else{return false;}
}


void IRSensor::irTask()
{
    int mean_val = 0;

    // Configuration ping and empty spurious notifications linked to setup
    ulTaskNotifyTake(pdTRUE, portMAX_DELAY);
    xTaskNotifyStateClear(NULL);

    for (;;)
    {
        // Wait operational ping from master
        ulTaskNotifyTake(pdTRUE, portMAX_DELAY);
        for(int i = 0; i < 5; i ++)
        {
            mean_val += static_cast<int>(read());
        }
        mean_val /= 5;  // Average value

        sendReading(static_cast<float>(mean_val));
        mean_val = 0;
    }
}


float IRSensor::read() const
{
    int raw = 0;

    if (xSemaphoreTake(adcMutex_, pdMS_TO_TICKS(20)) == pdTRUE) {
        adc_oneshot_read(adc1_handle, p_adc_channel, &raw);
        xSemaphoreGive(adcMutex_);
    } else {
        LOG_ERROR("IRSensor", "ADC mutex timeout");
        return -1.0f;
    }

    return static_cast<float>(raw);
}