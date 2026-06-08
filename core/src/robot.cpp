#include "robot.h"

// Trampolines
void Robot::sRobotTask(void* instance) {
    static_cast<Robot*>(instance)->test();
}
void Robot::sSensorTask(void* instance) {
    static_cast<Robot*>(instance)->sensorLoop();
}


// void Robot::sMotorTask(void* instance) {
//     static_cast<Robot*>(instance)->motorLoop();
// }
// void Robot::sNavTask(void* instance) {
//     static_cast<Robot*>(instance)->navLoop();
// }


// Constructor -> variables; init() -> hardware.
bool Robot::init()
{
    // install interrupt GPIO's driver
    esp_err_t err = gpio_install_isr_service(0);
    if (err != ESP_OK)
    {
        printf("ISR install failed: %s\n", esp_err_to_name(err));
    }

    robotTaskHandle_ = xTaskGetCurrentTaskHandle();

    // Queues
    commandQueue_ = xQueueCreate(5, sizeof(Direction));
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
    // xTaskCreate(sRobotTask, "Robot", 8192, this, 0, &robotTaskHandle_);
    xTaskCreate(sSensorTask, "Sensors", 8192, this, 4, &sensorTaskHandle_);
    xTaskCreate(UsSensor::sUSSensorTask, "US Sensors", 4096, &frontSensor_, 4, &USsensorTaskHandle_);
    xTaskCreate(IRSensor::sIRSensorTask, "IR Sensors left", 4096, &leftSensor_, 3, &IRsensor_LTaskHandle_);
    xTaskCreate(IRSensor::sIRSensorTask, "IR Sensors right", 4096, &rightSensor_, 3, &IRsensor_RTaskHandle_);
    // xTaskCreate(sMotorTask, "Motors", 4096, this, 2, &motorTaskHandle_);
    // xTaskCreate(sNavTask, "Navigation", 8192, this, 1, &navTaskHandle_);
    // xTaskCreate(sOdometryTask, "Odometry", 8192, this, 1, &odometryTaskHandle_);
    // xTaskCreate(sBlinkTask, "Blink", 4096, this, 0, &blinkTaskHandle_);

    // Set handles for each sensor task
    frontSensor_.setTaskHandle(USsensorTaskHandle_);
    leftSensor_.setTaskHandle(IRsensor_LTaskHandle_);
    rightSensor_.setTaskHandle(IRsensor_RTaskHandle_);

    // Sensors pin setup
    frontSensor_.ussensor_setup();
    leftSensor_.irsensor_setup();
    rightSensor_.irsensor_setup();

    frontSensor_.setQueue(usQueue_, sensorTaskHandle_);
    leftSensor_.setQueue(irLQueue_, sensorTaskHandle_);
    rightSensor_.setQueue(irRQueue_, sensorTaskHandle_);

    return true;
}


bool Robot::test()
{
    SensorReading r;

    // IR sensors require an extra ping to be ready
    xTaskNotifyGive(IRsensor_LTaskHandle_);
    xTaskNotifyGive(IRsensor_RTaskHandle_);
    
    for(int i = 0; i < 100; i++)
    {
        // Start orchestrator loop
        xTaskNotifyGive(sensorTaskHandle_);
        xTaskNotifyWait(0, 0, NULL, portMAX_DELAY);
        xQueueReceive(sensorQueue_, &r, portMAX_DELAY);

        if(r.isValid())
        {
            r.print();
        }
    }

    return true;
}


// Sensors orchestrator task
void Robot::sensorLoop() {
    SensorReading r;
    esp_task_wdt_add(NULL);
    
    // Ping for configuration
    ulTaskNotifyTake(pdTRUE, portMAX_DELAY);
    xTaskNotifyStateClear(NULL);

    // Wait for a ping to start
    ulTaskNotifyTake(pdTRUE, portMAX_DELAY);
    LOG_VERBOSE("Sensor Task", "Starting sensor loop")

    for (;;)
    {
        esp_task_wdt_reset();

        xTaskNotifyGive(USsensorTaskHandle_);
        xTaskNotifyGive(IRsensor_LTaskHandle_);
        xTaskNotifyGive(IRsensor_RTaskHandle_);

        xTaskNotifyWait(0, 0, NULL, portMAX_DELAY);
        xTaskNotifyWait(0, 0, NULL, portMAX_DELAY);
        xTaskNotifyWait(0, 0, NULL, portMAX_DELAY);

        xQueueReceive(usQueue_, &r.frontal, portMAX_DELAY);
        xQueueReceive(irLQueue_, &r.left, portMAX_DELAY);
        xQueueReceive(irRQueue_, &r.right, portMAX_DELAY);

        xQueueSend(sensorQueue_, &r, 0);
        xTaskNotifyGive(robotTaskHandle_);

        vTaskDelay(pdMS_TO_TICKS(1000));
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

void Robot::ending_loop()
{
    convert_to_morse("T", BLINK_GPIO);
}