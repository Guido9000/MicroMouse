#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "motor.h"

bool Motor::motor_setup()
{
    // Let the motor roar
    gpio_reset_pin((gpio_num_t)p_InPin1);
    gpio_set_direction((gpio_num_t)p_InPin1, GPIO_MODE_OUTPUT);
    gpio_reset_pin((gpio_num_t)p_InPin2);
    gpio_set_direction((gpio_num_t)p_InPin2, GPIO_MODE_OUTPUT);

    gpio_set_level((gpio_num_t)p_InPin1, 0);
    gpio_set_level((gpio_num_t)p_InPin2, 0);

    return true;
}

void Motor::rotate_forward()
{
    gpio_set_level((gpio_num_t)p_InPin1, 1);
    gpio_set_level((gpio_num_t)p_InPin2, 0);
}

void Motor::rotate_backward()
{
    gpio_set_level((gpio_num_t)p_InPin1, 0);
    gpio_set_level((gpio_num_t)p_InPin2, 1);
}

void Motor::stop()
{
    gpio_set_level((gpio_num_t)p_InPin1, 0);
    gpio_set_level((gpio_num_t)p_InPin2, 0);
}