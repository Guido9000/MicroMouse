#pragma once

#include <iostream>
#include "navigation.h"
#include "driver.h"
#include "sonar.h"
#include "maze_solver.h"
#include "maze.h"
#include "odometry.h"

class Axle;

extern "C" class Robot
{ 
    public:
        Robot()
            : rearAxle_(MOT_SLP_PIN, GPIO_NUM_22, GPIO_NUM_14, GPIO_NUM_25, GPIO_NUM_33, "rear"),
            frontSensor_(SEN_TRIG, SEN_ECHO, "front"),
            leftSensor_(SEN_TRIG, SEN_ECHO, "left"),
            rightSensor_(SEN_TRIG, SEN_ECHO, "right"),
            solver_(new RightHandSolver)
        {}
        bool test();
        bool explore();
        bool sprint();

    private:
        // Hardware
        Axle    rearAxle_;
        Sonar   frontSensor_;
        Sonar   leftSensor_;
        Sonar   rightSensor_;

        // Navigation
        mazeGrid    maze_;
        Navigation  navigator_;
        ISolver*    solver_;
        Odometry    odometry_;

        void rotateByDegrees(float degrees);
        void stop();
        bool nextCenterReached();
        bool isCentered();
        float calibrateDist();
        void keepEqDistance();
        bool initializePosition();
};