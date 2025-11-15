#pragma once

#include "sonar.h"

// Parametri da passare al task dei sensori
typedef struct {
    Sonar* sonar;
    const char* name;
} SensorTaskParams;

// Prototipo del task
extern "C" void Task_sensors(void* pvParameters);