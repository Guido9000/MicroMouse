#pragma once

#include <iostream>
#include <string>
#include "driver/gpio.h"
#include "motor.h"

extern "C" class Axle
{ 
    public:
        Axle() = default;
        explicit Axle(int SLP, int AIN1, int AIN2, int BIN1, int BIN2, std::string name)
            : p_SLP(SLP), 
            motor_left(AIN1, AIN2, "left"),
            motor_right(BIN1, BIN2, "right"),
            p_name(name)
        {
            if(driver_setup()){std::cout << name << " axle is online" << std::endl;}
        }

        bool nextMove();
        void move_forward();
        void move_backward();
        void stop();

    private:
        int p_SLP;
        Motor motor_left;   //here they are created in the class
        Motor motor_right;  //if in setup, they are destroyed at the end of the setup
        std::string p_name;

        bool driver_setup();

};