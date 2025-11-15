#include <cstdio>
#include "tasks.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

void Task_sensors(void* pvParameters)
{
    //converte il void* generico in un puntatore a SensorTaskParams
    SensorTaskParams* params = (SensorTaskParams*) pvParameters;

    //accesso al membro sonar/name della struct
    Sonar* sonar = params->sonar;
    const char* name = params->name;

    while (true)
    {
        float d = sonar->read();
        printf("[%s] Distance = %.2f cm\n", name, d);

        vTaskDelay(50 / portTICK_PERIOD_MS);
    }
}
