#include <iostream>
#include "hal/interfaces.h"
#include "hal/mock_sensor.h"

int main() {
    MockSensor sensor;
    MockDrive  drive;

    sensor.setNextReading(200.0f);

    std::cout << "Distanza: " << sensor.getDistanceMM() << " mm\n";
    std::cout << "Parete: "   << sensor.isWallDetected() << "\n";

    return 0;
}