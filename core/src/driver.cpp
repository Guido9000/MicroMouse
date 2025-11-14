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

void Axle::move_forward()
{
    motor_left.rotate_forward();
    motor_right.rotate_forward();
}

void Axle::move_backward()
{
    motor_left.rotate_backward();
    motor_right.rotate_backward();
}

void Axle::stop()
{
    motor_left.stop();
    motor_right.stop();
}