#include "robot.h"


// xTaskCreatePinnedToCore(
//     task1,              // function name
//     "Task sensors",     // task name
//     8192,               // stack size in bytes (increase for large functions)
// NULL,                   // task input
//     3,                  // task priority
//     &task1_handle,      // task handle (to interact with the task from other tasks)
//     1                   // core
// );

// xTaskCreatePinnedToCore(
// task2,                  // function name
// "Task motors",          // task name
//     8192,               // stack size in bytes (increase for large functions)
//     NULL,               // task input
//     2,                  // task priority
//     &task2_handle,      // task handle (to interact with the task from outside)
//     0                   // core
// );

// xTaskCreatePinnedToCore(
//     task3,              // function name
//     "Task navigation",  // task name
//     8192,               // stack size in bytes (increase for large functions)
//     NULL,               // task input
//     1,                  // task priority
//     &task3_handle,      // task handle (to interact with the task from other tasks)
//     0                   // core
// );


// int count1 = 0;
// int count2 = 0;
// TaskHandle_t task1_handle = NULL;

// void task1 (void* parameters)
// {
//     // add task to watchdog list
//     esp_task_wdt_add(NULL);

//     for(;;)
//     {
//         // reset watchdog timer
//         esp_task_wdt_reset();
//         LOG_INFO("Task 1 count ", count1);

//         count1++;
//         vTaskDelay(pdMS_TO_TICKS(1000));
//     }

//     // delete task from watchdog list
//     esp_task_wdt_delete(NULL);
// }

// void task2 (void* parameters)
// {
//     // add task to watchdog list
//     esp_task_wdt_add(NULL);

//     for(;;)
//     {
//         // reset watchdog timer
//         esp_task_wdt_reset();
//         LOG_INFO("Task 2 count ", count2);

//         count2++;
//         vTaskDelay(pdMS_TO_TICKS(1000));
//     }
    
//     // delete task from watchdog list
//     esp_task_wdt_delete(NULL);
// }

bool Robot::test()
{

    // if(count1 > 2 && task1_handle != NULL && count2 < 5)
    // {
    //     vTaskSuspend(task1_handle);
    // }
    // if(count2 == 10 && task1_handle != NULL)
    // {
    //     vTaskResume(task1_handle);
    // }

    // rearAxle_.rotate_forward();
    // std::cout << "Front sensor: " << frontSensor_.read() << std::endl;
    // std::cout << "Left sensor: " << leftSensor_.read() << std::endl;
    // std::cout << "Right sensor: " << rightSensor_.read() << std::endl;

    // vTaskDelay(pdMS_TO_TICKS(40));

    // if(!frontSensor_.theresWall())
    // {
    //     std::cout << "free space" << std::endl;
        // rearAxle_.move_forward(40);
        // vTaskDelay(pdMS_TO_TICKS(2000));
        // rearAxle_.stop();
        // vTaskDelay(pdMS_TO_TICKS(2000));
        // rearAxle_.move_backward(40);
        // vTaskDelay(pdMS_TO_TICKS(2000));
        // rearAxle_.stop();
        // rearAxle_.rotate(90.0);
    // }
    // else
    // {
    //     std::cout << "wall" << std::endl;
    //     rearAxle_.rotate(90.0);
    //     // rearAxle_.stop();
    // }

    return true;
}


bool Robot::init()
{
    // crea le code prima dei task
    commandQueue_ = xQueueCreate(5, sizeof(Direction));

    // single sensor queue
    usQueue_   = xQueueCreate(1, sizeof(float));
    irLQueue_  = xQueueCreate(1, sizeof(float));
    irRQueue_  = xQueueCreate(1, sizeof(float));
    sensorQueue_ = xQueueCreate(5, sizeof(SensorReading));

    // create tasks
    // sMotorTask,         function name
    // "Task motors",      task name
    // 8192,               stack size in bytes (increase for large functions)
    // NULL,               task input
    // 2,                  task priority
    // &task2_handle,      task handle (to interact with the task from outside)
    xTaskCreate(sSensorTask, "Sensors", 8192, this, 4, &sensorTaskHandle_);
    xTaskCreate(UsSensor::sUSSensorTask, "US Sensors", 4096, &frontSensor_, 4, &USsensorTaskHandle_);
    xTaskCreate(IRSensor::sIRSensorTask, "IR Sensors left", 4096, &leftSensor_, 3, &IRsensor_LTaskHandle_);
    xTaskCreate(IRSensor::sIRSensorTask, "IR Sensors right", 4096, &rightSensor_, 3, &IRsensor_RTaskHandle_);
    // xTaskCreate(sMotorTask, "Motors", 4096, this, 2, &motorTaskHandle_);
    // xTaskCreate(sNavTask, "Navigation", 8192, this, 1, &navTaskHandle_);
    // xTaskCreate(sOdometryTask, "Odometry", 8192, this, 1, &odometryTaskHandle_);
    // xTaskCreate(sBlinkTask, "Blink", 4096, this, 0, &blinkTaskHandle_);

    frontSensor_.setQueue(usQueue_, sensorTaskHandle_);
    leftSensor_.setQueue(irLQueue_, sensorTaskHandle_);
    rightSensor_.setQueue(irRQueue_, sensorTaskHandle_);

    return true;
}


// trampolini — convertono void* in Robot* e chiamano il metodo reale
void Robot::sSensorTask(void* instance) {
    static_cast<Robot*>(instance)->sensorLoop();
}
// void Robot::sMotorTask(void* instance) {
//     static_cast<Robot*>(instance)->motorLoop();
// }
// void Robot::sNavTask(void* instance) {
//     static_cast<Robot*>(instance)->navLoop();
// }


// void Robot::sensorLoop() {
//     esp_task_wdt_add(NULL);

    // for(;;) {
    //     esp_task_wdt_reset();

    //     sSensorTask();

    //     // Start frontal measure
    //     .frontMM = sUSSensorTask();    // frontSensor_.getDistanceMM();
    //     .leftMM  = sIRSensor_LTask();  // leftSensor_.getDistanceMM();
    //     .rightMM = sIRSensor_RTask();  // rightSensor_.getDistanceMM();
        
    //     SensorReading reading = {
    //         .frontMM = frontSensor_.getDistanceMM(),
    //         .leftMM  = leftSensor_.getDistanceMM(),
    //         .rightMM = rightSensor_.getDistanceMM()
    //     };
    //     xQueueSend(sensorQueue_, &reading, 0);

    //     vTaskDelay(pdMS_TO_TICKS(50));
//     }
// }


void Robot::sensorLoop() {
    esp_task_wdt_add(NULL);

    for (;;)
    {
        esp_task_wdt_reset();

        // xTaskNotifyGive(USsensorTaskHandle_);
        // xTaskNotifyGive(IRsensor_LTaskHandle_);

        SensorReading r;

        xQueueReceive(sensorQueue_, &r, portMAX_DELAY);

        // usa dati
        vTaskDelay(pdMS_TO_TICKS(50));
    }
}


// void Robot::navLoop() {
//     esp_task_wdt_add(NULL);
//     SensorReading reading;
//     for(;;) {
//         esp_task_wdt_reset();

//         if(xQueueReceive(sensorQueue_, &reading, pdMS_TO_TICKS(100))) {
//             navigator_.updateWalls(maze_, reading);
//             Direction next = solver_->nextMove(maze_, navigator_.getPosition());
//             xQueueSend(commandQueue_, &next, 0);
//         }

//         vTaskDelay(pdMS_TO_TICKS(100));
//     }
// }

// void Robot::motorLoop() {
//     esp_task_wdt_add(NULL);
//     Direction command;
//     for(;;) {
//         esp_task_wdt_reset();

//         if(xQueueReceive(commandQueue_, &command, pdMS_TO_TICKS(100))) {
//             rearAxle_.move(command);
//         }

//         vTaskDelay(pdMS_TO_TICKS(10));
//     }
// }


bool Robot::explore()
{
    float time = 0; // TODO substitute with clock
    float speed = 0; // TODO substitute speed
    float angle = 0;

    Direction next;
    Position myPosition = navigator_.getPosition();

    // get centered in (0,0)
    if(initializePosition())
    {
        // use navigation to find the goal
        while(!maze_.isGoal(myPosition.x, myPosition.y))
        {
            // Orient robot direction
            /* FRECCINA!!!! */
            next = solver_->nextStep(maze_, myPosition); // next is the rotation to perform
            // angle = navigator_.calculateRotation(myPosition.heading, next);
            rearAxle_.rotate(angle); // rotate
            navigator_.setHeading(myPosition); //update heading

            // Initialize odometry
            odometry_.takeTime(time); // inizializza cronometro per odometria ruote
            // odometry_.updateSensorLastMeasure(frontSensor_.read()); // initialize front sensor for odometry

            // Move ahead
            rearAxle_.move_forward(100); // Move forward into next corridor
            // rearAxle_.nextCenterReached(); // Probably useless, substituted with odometry

            // Almost reaching the next center cell: update navigation position and set walls
            if(odometry_.wheelSpaceTraveled(time, speed) >= CELL_SIZE_MM * 0.9)
            {
                if(!maze_.isBoarder(myPosition.x, myPosition.y, myPosition.heading))
                {    
                    navigator_.setPosition(maze_.adiacentCell(myPosition.x, myPosition.y, myPosition.heading));  // update navigation position
                }
                else
                {
                    LOG_ERROR("Position", "I cannot go beyond the border");
                }
                navigator_.updateWalls(maze_, frontSensor_, leftSensor_, rightSensor_);
                /* TODO FRECCINE! */
                next = solver_->nextStep(maze_, myPosition); // be prepared for next action
            }

            // Reach next center cell with wheelSpaceTraveled(time, speed) = CELL_SIZE_MM and iterate the while loop
            if(odometry_.wheelSpaceTraveled(time, speed) >= CELL_SIZE_MM)
            {
                // if turn available/necessary, be ready to stop
                if (myPosition.heading != next)
                {
                    //stop, next iteration you'll turn
                    rearAxle_.stop();
                }
                // else go stright without stopping
                else
                {
                    continue;
                }
            }

        }
    }
    else
    {
        LOG_ERROR("Position", "Initialization position (0,0) failed");
        return false;
    }

    LOG_INFO("Robot", "Exploration is complete");
    return true;
}


bool Robot::sprint()
{
    // read the maze to sprint

    return true;
}


bool Robot::initializePosition()
{
    // Verify to be in a blind spot
    // Center in the cell
    return true;
}

void Robot::rotateByDegrees(float degrees)
{
    if(degrees > 0)
    {
        // applica spinta positiva a motore dx
        // applica spinta negativa a motore sx
        // stop
    }
    else if(degrees < 0)
    {
        // applica spinta positiva a motore sx
        // applica spinta negativa a motore dx
        // stop
    }
}


void Robot::stop()
{

}


bool Robot::nextCenterReached()
{
    double spaceTraveled = 0;
    float time = 0;     // TODO Pass speed through the function
    float speed = 0;    // TODO Pass speed through the function

    std::cout << "TEST DISTANZA" << static_cast<int> (odometry_.wheelSpaceTraveled(time, speed)) << " " << odometry_.wheelSpaceTraveled(time, speed) << std::endl;
    int tmp = static_cast<int> (odometry_.wheelSpaceTraveled(time, speed));

    while(spaceTraveled > (tmp % 180))
    {
        spaceTraveled = (tmp % 180);
        return false;
    }
    return true;
}


bool Robot::isCentered()
{

    return 0;
}


float Robot::calibrateDist()
{
    /* TODO adapt MockSensor for Sonar */
    // MockSensor frontSensor;
    // if(isCentered() == 1)
    // {
    //     frontSensor.getDistanceMM();
    //     //TODO: Correct distance. Go to proper center
    // }

    return 0.0f;
}

//Center the robot in the cell to keep same distance from left and right
void Robot::keepEqDistance()
{
    // Possible first approach:
    // 1) rileva differenza dx vs sx
    // 2) applica rotazione verso centro
    // 3) avanza fino a rendere dx = sx
    // 4) applica anti rotazione

    /* TODO: MockSensor leftSensor_, rightSensor_;
        e` scritto per Mocksensor, va sistemato per Sonar*/
    // // TODO: left and right sensor must be passed from the extern
    // // MockSensor
    // MockSensor leftSensor_, rightSensor_;
    // float gap;
    // float leftWheelSpeed;
    // float rightWheelSpeed;
    // float normConst;

    // normConst = leftSensor_.getDistanceMM() + rightSensor_.getDistanceMM();
    // gap = leftSensor_.getDistanceMM() - rightSensor_.getDistanceMM();

    // if(leftSensor_.isWallDetected() && rightSensor_.isWallDetected())
    // {
    //     if(abs(gap) > 5.0)
    //     {
    //         if(gap > 0)
    //         {
    //             rotateByDegrees(-45.0);
    //             // Go ahead until gap = 0; (reachCenter?)
    //             rotateByDegrees(45.0);

    //             // TODO
    //             // Dynamic algorithm
    //             // Reduce right wheel speed
    //             // rightWheelSpeed = 0.2 * gap / normConst;
    //         }
    //         else
    //         {
    //             rotateByDegrees(45.0);
    //             // Go ahead until gap = 0;
    //             rotateByDegrees(-45.0);
                
    //             // TODO
    //             // Dynamic algorithm
    //             // Reduce left wheel speed
    //             // leftWheelSpeed = 0.2 * gap / normConst;
    //         }
    //     }
    // }
} 