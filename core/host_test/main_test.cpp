#define LOG_LEVEL_LOCAL LOG_DEBUG
#define HOST_BUILD
// #include "esp_log.h"

#include <iostream>
#include "../src/hal/interfaces.h"
#include "../src/hal/mock_sensor.h"
#include "../src/navigation/maze.cpp"
#include "../inc/log.h"


int main() {
    MockSensor sensor;
    MockMotor motor;
    maze_grid grid;

    sensor.setNextReading(20.0f);

    std::cout << "Distanza: " << sensor.getDistanceMM() << " mm\n";
    std::cout << "Parete: "   << sensor.isWallDetected() << "\n";

    // std::cout << "Cell number: " <<  << std::endl;
    grid.setWall(2, 3, SUD);
    grid.hasWall(2, 3, SUD);
    grid.print(2,3);

    return 0;
}