#pragma once

#include <iostream>
#include "navigation.h"
#include "driver.h"
#include "sonar.h"
#include "maze_solver.h"
#include "maze.h"


extern "C" class Robot
{ 
    public:
        void init();
        bool explore();
        bool sprint();

    private:
        // Navigation
        mazeGrid    maze_;
        Navigation  navigator_;
        ISolver*    solver_;

        // Hardware
        Axle    rearAxle_;
        Sonar   frontSensor_;
        Sonar   leftSensor_;
        Sonar   rightSensor_;
 
        void rotateByDegrees(float degrees);
        void stop();
        void reachCenter();
        bool isCentered();
        float calibrateDist();
        void keepEqDistance();
};