#pragma once

#include <iostream>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"
#include "esp_task_wdt.h"
#include "driver/gpio.h"
#include "navigation.h"
#include "driver.h"
#include "sensor.h"
#include "maze_solver.h"
#include "maze.h"
#include "morse.h"
#include "odometry.h"
#include "controller.h"

class Axle;

class Robot
{ 
    public:
        Robot()
            : rearAxle_(MOT_SLP_PIN, MOT_B1_PIN, MOT_B2_PIN, MOT_A2_PIN, MOT_A1_PIN, "rear"),
            frontSensor_(SEN_TRIG, SEN_ECHO, "front"),
            leftSensor_(ADC_CHANNEL_6, "left"),
            rightSensor_(ADC_CHANNEL_7, "right"),
            solver_(new RightHandSolver)
        {}
        
        bool init();    // Tasks init
        void deinit();  // Tasks destructor
        bool test();
        bool explore();
        bool sprint();
        void ending_loop();

    private:
        // Hardware
        Axle        rearAxle_;
        UsSensor    frontSensor_;
        IRSensor    leftSensor_;
        IRSensor    rightSensor_;

        // Navigation
        mazeGrid    maze_;
        Navigation  navigator_;
        ISolver*    solver_;
        Odometry    odometry_;

        // Controller
        Controller controller_;

        void rotateByDegrees(float degrees);
        void stop();
        bool nextCenterReached();
        bool isCentered();
        float calibrateDist();
        void keepEqDistance();
        bool initializePosition();

        // Task handles
        TaskHandle_t robotTaskHandle_       = NULL;
        TaskHandle_t sensorTaskHandle_      = NULL;
        TaskHandle_t USsensorTaskHandle_    = NULL;
        TaskHandle_t IRsensor_LTaskHandle_  = NULL;
        TaskHandle_t IRsensor_RTaskHandle_  = NULL;
        TaskHandle_t motorTaskHandle_       = NULL;
        TaskHandle_t navTaskHandle_         = NULL;
        TaskHandle_t odometryTaskHandle_    = NULL;
        TaskHandle_t blinkTaskHandle_       = NULL;

        // Queue for communication
        QueueHandle_t usQueue_      = NULL;
        QueueHandle_t irLQueue_     = NULL;
        QueueHandle_t irRQueue_     = NULL;
        QueueHandle_t sensorQueue_  = NULL;
        QueueHandle_t commandQueue_ = NULL;

        // Static trampolines
        static void sRobotTask(void* instance);
        static void sSensorTask(void* instance);
        static void sUSSensorTask(void* instance);
        static void sIRSensor_LTask(void* instance);
        static void sIRSensor_RTask(void* instance);
        // static void sMotorTask(void* instance);
        // static void sNavTask(void* instance);
        // static void sOdometryTask(void* instance);
        // static void sBlinkTask(void* instance);

        // Actual loop
        void sensorLoop();
        // void motorLoop();
        // void navLoop();

};