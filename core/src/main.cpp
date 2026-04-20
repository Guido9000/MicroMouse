#define LOG_LEVEL_LOCAL ESP_LOG_VERBOSE
#include "driver/gpio.h"    //General Purpose Input/Output
#include "esp_log.h"

#include "inc/main.h"
#include "pin.h"
#include <thread>
#include <chrono>

#define LOG_TAG "MAIN"


// esp_err_t Main::setup() {
//     ESP_LOGI(LOG_TAG, "Setup complete!");
//     return ESP_OK;
// }

// void Main::loop() {
//     float dist = frontSensor_.getDistanceMM();

//     if (dist < 300.0f) {
//         drive_.stop();
//     } else {
//         drive_.moveForward(SPEED_EXPLORE_MM_S);
//     }

//     // Select clock
//     std::this_thread::sleep_for(std::chrono::seconds(1));
//     // vTaskDelay(pdSECOND);
// }


//////////////////// OLD TEST PER INIZIARE
TaskHandle_t FrontSensor;
SemaphoreHandle_t xSemaphore = NULL;
//TaskHandle_t Task2Handle = NULL;
static Sonar sonar_front(SEN_TRIG, SEN_ECHO, "front");
static SensorTaskParams front_params = {
    .sonar = &sonar_front,
    .name = "front"
};

using namespace std;

static Main my_main;

//link to C
extern "C" void app_main(void)
{
    esp_chip_info_t chip_info;
    //uint32_t flash_size;
    esp_chip_info(&chip_info);

    // Configuro il GPIO come uscita
    gpio_reset_pin((gpio_num_t)BLINK_GPIO);
    gpio_set_direction((gpio_num_t)BLINK_GPIO, GPIO_MODE_OUTPUT);

    ESP_ERROR_CHECK(my_main.setup());
    my_main.hello_world(chip_info);

    convert_to_morse("SOS", BLINK_GPIO);

    //int i = 0;
    //while (i < 1)
    //{
        xSemaphore = xSemaphoreCreateBinary();

        // cout << "Timer output in ms program initiation: " << esp_timer_get_time()/1000 << endl;
        // xTaskCreatePinnedToCore(Task_sensors, "Task_sensors", 4096, &front_params, 1, &FrontSensor, 1);

        // if(xSemaphoreTake(xSemaphore, portMAX_DELAY))
        // {
        //     cout << "Program complete: " << esp_timer_get_time()/1000 << endl;
        // }

        my_main.loop();
    //    i++;
    //}

    ESP_LOGI(LOG_TAG, "Goodbye");
    vTaskDelete(FrontSensor);
}

esp_err_t Main::setup(void)
{
    // Initialize the serial UART at 115200 baud
    //Serial.begin(115200);

    esp_err_t status{ESP_OK};
    //Non crea un nuovo oggetto locale, ma usa l’operatore di assegnazione per copiare i valori dentro il membro esistente.
    front_axle = Axle(MOT_SLP_PIN, GPIO_NUM_26, GPIO_NUM_14, GPIO_NUM_25, GPIO_NUM_33, "front");
                        //trig,      echo
    sonar_front = Sonar(SEN_TRIG, SEN_ECHO, "front");
    
    /*xTaskCreatePinnedToCore(
    sonar_front.read_distance,             // Task function
    "sonar_front",           // Task name
    10000,             // Stack size (bytes)
    NULL,              // Parameters
    1,                 // Priority
    &FrontSensor,      // Task handle
    1                  // Core 1
  );*/
 
    ESP_LOGI(LOG_TAG, "Setup complete!");
    
    return status;
}

void Main::hello_world(esp_chip_info_t chip_info)
{
    ESP_LOGI(LOG_TAG,
        "This is %s chip with %d CPU core(s), %s%s%s%s",
        CONFIG_IDF_TARGET,
        chip_info.cores,
        (chip_info.features & CHIP_FEATURE_WIFI_BGN) ? "WiFi/" : "",
        (chip_info.features & CHIP_FEATURE_BT) ? "BT" : "",
        (chip_info.features & CHIP_FEATURE_BLE) ? "BLE" : "",
        (chip_info.features & CHIP_FEATURE_IEEE802154) ? ", 802.15.4 (Zigbee/Thread)" : "");

    //Led opening message
    
}

void Main::loop(void)
{
    float dist = 0;

    dist = sonar_front.read();
    cout << dist << " cm" << endl;
    if(dist < 0)
    {
        front_axle.stop();
    }
    else{
        front_axle.move_forward();
    }
    
    vTaskDelay(pdSECOND);
}

/*void Task_sensors(void* pvParameters)
{
    int front;
    int read_state = 0;

    while(true)
    {
        switch(read_state) {
            case 0:
                front = sonar_front.read();
                read_state = 1;
                break;

            case 1:
                //left = sonar_left.read();
                read_state = 2;
                break;

            case 2:
                //right = sonar_right.read();
                read_state = 0;
                break;
        }

        vTaskDelay(50 / portTICK_PERIOD_MS);
    }

    vTaskDelete(NULL);
}
*/