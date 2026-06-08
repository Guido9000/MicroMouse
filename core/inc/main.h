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
#include "esp_task_wdt.h"
#include "esp_log.h"    //
// #include "interfaces.h"
#include "morse.h"
#include "robot.h"

#define pdSECOND pdMS_TO_TICKS(1000)

class Main final
{
    public:
        // Main() = default;

        esp_err_t setup(void);
        void hello_world(esp_chip_info_t);
        void loop(void);
        Robot robot_;

    private:
     
};