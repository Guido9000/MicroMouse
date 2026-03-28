#include "esp_log.h"
#include "main.h"

// Scegli UNO dei due blocchi:

// --- MODALITÀ MOCK (senza hardware) ---
#include "hal/mock_sensor.h"
static MockSensor frontSensor;
static MockDrive drive;

// --- MODALITÀ REALE (con hardware) ---
// #include "sonar.h"
// #include "driver.h"
// #include "hal/pins.h"
// static Sonar  frontSensor(SEN_TRIG, SEN_ECHO, "front");
// static Axle   drive(MOT_SLP_PIN, GPIO_NUM_26, ...);

static Main my_main(frontSensor, drive);

extern "C" void app_main(void) {
    ESP_ERROR_CHECK(my_main.setup());

    // In futuro qui lancerai i task FreeRTOS
    while (true) {
        my_main.loop();
    }
}