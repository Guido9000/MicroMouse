

#define LOG_LEVEL_LOCAL ESP_LOG_VERBOSE
#include "driver/gpio.h"    //General Purpose Input/Output
#include "esp_log.h"

#include "main.h"

#define LOG_TAG "MAIN"

// set with idf.py menuconfig
#define BLINK_GPIO   CONFIG_BLINK_GPIO      //
#define BLINK_PERIOD CONFIG_BLINK_PERIOD    //
// Define driver slp
#define MOT_SLP_PIN GPIO_NUM_22
// Define the control inputs
#define MOT_A1_PIN GPIO_NUM_26
#define MOT_A2_PIN GPIO_NUM_14
#define MOT_B1_PIN GPIO_NUM_25
#define MOT_B2_PIN GPIO_NUM_33

// Define the front sensor inputs
#define SEN_TRIG GPIO_NUM_18
#define SEN_ECHO GPIO_NUM_34

TaskHandle_t FrontSensor = NULL;
//TaskHandle_t Task2Handle = NULL;

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

    while (true)
    {
        my_main.loop();
    }

    ESP_LOGI(LOG_TAG, "Goodbye");
}

esp_err_t Main::setup(void)
{
    // Initialize the serial UART at 115200 baud
    //Serial.begin(115200);

    esp_err_t status{ESP_OK};
    //Non crea un nuovo oggetto locale, ma usa l’operatore di assegnazione per copiare i valori dentro il membro esistente.
    front_axle = Axle(GPIO_NUM_22, GPIO_NUM_26, GPIO_NUM_14, GPIO_NUM_25, GPIO_NUM_33, "front");
                        //trig,      echo
    front_sonar = Sonar(SEN_TRIG, SEN_ECHO, "front");
    /*xTaskCreatePinnedToCore(
    front_sonar.read_distance,             // Task function
    "front_sonar",           // Task name
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

    dist = front_sonar.read_distance();
    cout << dist << " cm" << endl;
    if(dist < 300)
    {
        front_axle.stop();
    }
    else{
        front_axle.move_forward();
    }
    
    vTaskDelay(pdSECOND);
}