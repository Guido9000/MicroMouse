#pragma once

#include <stdio.h>
#include <iostream>
#include <string>
#include "freertos/FreeRTOS.h"  //
#include "freertos/timers.h"
#include "freertos/task.h"  //
#include "freertos/semphr.h"  //
#include "driver/gpio.h"    // For GPIO control
#include "esp_chip_info.h"  //
#include "esp_flash.h"
#include "esp_system.h"
#include "esp_log.h"    //
// #include "hal/interfaces.h"
#include "morse.h"
#include "motor.h"
#include "driver.h"
#include "sonar.h"
#include "tasks.h"
// #include "hal/pin.h"
// #include "hal/config.h"

#define pdSECOND pdMS_TO_TICKS(1000)


// class Main final {
// public:
//     // Riceve le dipendenze dall'esterno — non le crea lui
//     Main(IDistanceSensor& frontSensor, IDrive& drive)
//         : frontSensor_(frontSensor), drive_(drive) {}

//     esp_err_t setup();
//     void      loop();

// private:
//     IDistanceSensor& frontSensor_;
//     IDrive&          drive_;
// };

void Task_sensors(void* pvParameters);
void vTask2(void* pvParameters);
void vTaskN(void* pvParameters);

class Main final
{
public:
    Main() = default;

    esp_err_t setup(void);
    void hello_world(esp_chip_info_t);
    void loop(void);

private:
    // build as a member of class Main, configure it in setup. It'll be not destroyed at the end of setup
    Axle front_axle{0, 0, 0, 0, 0, "undefined"};    //GRAFFE!
    Axle rear_axle{0, 0, 0, 0, 0, "undefined"};
    Sonar sonar_front{0, 0, "undefined"};
    
};