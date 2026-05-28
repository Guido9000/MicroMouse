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
    int duty_cycle = motor_left.speedToDuty(throttle);

    motor_left.rotate_forward(duty_cycle);
    motor_right.rotate_forward(duty_cycle);
}


void Axle::move_backward(int throttle)
{
    int duty_cycle = motor_left.speedToDuty(throttle);

    motor_left.rotate_backward(duty_cycle);
    motor_right.rotate_backward(duty_cycle);
}


void Axle::stop()
{
    motor_left.stop();
    motor_right.stop();
}


// 90 degrees rotation
bool Axle::rotate(float angle)
{
    int throttle = SPEED_ROTATION;
    int duty_cycle = motor_left.speedToDuty(throttle);

    // Rotate L/R/Back
    if(angle > 0)
    {
        motor_left.rotate_forward(duty_cycle);
        motor_right.rotate_backward(duty_cycle);
        vTaskDelay(pdMS_TO_TICKS(200));
        motor_left.stop();
        motor_right.stop();
    }
    else if(angle < 0)
    {
        motor_left.rotate_backward(duty_cycle);
        motor_right.rotate_forward(duty_cycle);
        vTaskDelay(pdMS_TO_TICKS(200));
        motor_left.stop();
        motor_right.stop();    
    }

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