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
#include "controller.cpp"


int main() {
    MockSensor sensor;
    MockMotor motor;
    mazeGrid grid;
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
 
    }

    return 0;
}


// esp_err_t Main::setup() {
//     robot_.init();
//     return ESP_OK;
// }

// void Main::solveTheMaze() {
//     robot_.explore();    // esplora finché non trova il centro
// }

// void Main::runInTheMaze() {
//     robot_.sprint();     // corre il percorso ottimale
// }