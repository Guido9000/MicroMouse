#define LOG_LEVEL_LOCAL LOG_DEBUG
#define HOST_BUILD
// #include "esp_log.h"
#pragma once
#include <iostream>
#include "interfaces.h"
#include "mock_sensor.h"
#include "maze.cpp"
#include "navigation.cpp"
#include "log.h"
#include "maze_solver.cpp"
#include "robot.cpp"


int main() {
    MockSensor sensor;
    MockMotor motor;
    maze_grid grid;
    ISolver* solver_ = new RightHandSolver();

    // Set wall distance by hand
    sensor.setNextReading(20.0f);

    std::cout << "Distanza: " << sensor.getDistanceMM() << " mm\n";
    if(sensor.isWallDetected())
    {
        LOG_INFO("Sensor", "Wall detected");

        grid.setWall(7, 7, WEST);
        cout << grid.isGoal(8,8) << endl;
        // grid.hasWall(2, 3, EAST);
        // grid.print(2,3);
        // nav.turn_right();
        // nav.turn_right();
        // nav.turn_right();
        // nav.turn_right();
        // nav.turn_right();
        // nav.turn_left();
        // nav.opposite_direction();       
    }

    return 0;
}