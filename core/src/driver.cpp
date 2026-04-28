#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver.h"


bool Axle::driver_setup()
{
    // Wake up the driver
    gpio_reset_pin((gpio_num_t)p_SLP);
    gpio_set_direction((gpio_num_t)p_SLP, GPIO_MODE_OUTPUT);
    gpio_set_level((gpio_num_t)p_SLP, 1);

    return true;
}


void Axle::move_forward(int throttle)
{
    // float speed;    // TODO Pass speed through the function
    // speed = 0;

    motor_left.rotate_forward(throttle);
    motor_right.rotate_forward(throttle);
}


void Axle::move_backward()
{
    // float speed;    // TODO Pass speed through the function
    // speed = 0;

    motor_left.rotate_backward();
    motor_right.rotate_backward();
}


void Axle::stop()
{
    motor_left.stop();
    motor_right.stop();
}


// 90 degrees rotation
bool Axle::prepareNextMove(Direction next)
{
    // Rotate L/R/Back

    return true;
}


bool Axle::NextMove()
{

    return true;
}


void Axle::printAxlePins()
{
    motor_left.printSleepPins();
    motor_left.printPins();
    motor_right.printPins();
}