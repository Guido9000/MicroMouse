#pragma once

#include <iostream>
#include <string>
#include "driver/gpio.h"
#include "motor.h"
#include "direction.h"

extern "C" class Axle
{ 
    public:
        // Axle() = default;
        explicit Axle(gpio_num_t SLP, gpio_num_t AIN1, gpio_num_t AIN2, gpio_num_t BIN1, gpio_num_t BIN2, std::string name)
            : p_SLP(SLP), 
            motor_left(AIN1, AIN2, LEDC_CHANNEL_0, LEDC_CHANNEL_1, "left"),
            motor_right(BIN1, BIN2, LEDC_CHANNEL_2, LEDC_CHANNEL_3, "right"),
            p_name(name)
        {
            if(driver_setup()){std::cout << name << " axle is online" << std::endl;}
        }

        bool prepareNextMove(Direction next);
        bool NextMove();
        void move_forward(int throttle);
        void move_backward();
        void stop();
        void printAxlePins();

    private:
        int p_SLP;
        Motor motor_left;   //here they are created in the class
        Motor motor_right;  //if in setup, they are destroyed at the end of the setup
        std::string p_name;

        bool driver_setup();

};