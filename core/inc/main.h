#pragma once

#include <stdio.h>
#include <iostream>
#include <string>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include "esp_chip_info.h"
#include "esp_flash.h"
#include "esp_system.h"
#include "morse.h"
#include "motor.h"
#include "driver.h"
#include "sonar.h"

#define pdSECOND pdMS_TO_TICKS(1000)


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
    Sonar front_sonar{0, 0, "undefined"};
};