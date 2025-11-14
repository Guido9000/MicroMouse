#pragma once

#include <iostream>
#include <string>
#include "driver/gpio.h"

extern "C" class Motor
{ 
    public:
        explicit Motor(int InPin1, int InPin2, const std::string& name)
            : p_InPin1(InPin1), p_InPin2(InPin2), p_name(name) // initializer list: inizializza direttamente i membri della classe, prima che venga eseguito il corpo del costruttore.
        {
            if(motor_setup()){std::cout << "Motor " << name << " is online" << std::endl;}
        }

        void rotate_forward();
        void rotate_backward();
        void stop();

    private:    // non voglio che il codice esterno li chiami per sbaglio
        int p_InPin1;
        int p_InPin2;
        std::string p_name;
        
        bool motor_setup();
};