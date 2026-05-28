#pragma once

#include <iostream>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include "navigation.h"
#include "driver.h"
#include "sonar.h"
#include "maze_solver.h"
#include "maze.h"
#include "odometry.h"
#include "controller.h"

class Axle;

extern "C" class Robot
{ 
    public:
        Robot()
            : rearAxle_(MOT_SLP_PIN, MOT_B1_PIN, MOT_B2_PIN, MOT_A2_PIN, MOT_A1_PIN, "rear"),
            frontSensor_(SEN_TRIG, SEN_ECHO, "front"),
            leftSensor_(ADC_CHANNEL_6, "left"),
            rightSensor_(ADC_CHANNEL_7, "right"),
            solver_(new RightHandSolver)
        {}
        bool test();
        bool explore();
        bool sprint();

    private:
        // Hardware
        Axle    rearAxle_;
        Sonar   frontSensor_;
        IRSensor   leftSensor_;
        IRSensor   rightSensor_;

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
};