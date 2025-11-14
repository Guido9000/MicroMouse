#pragma once

#include <iostream>
#include <string>
#include "driver/gpio.h"
#include "esp_timer.h"
#include "sonar.h"

extern "C" class Sonar
{ 
    public:
        Sonar() = default;
        explicit Sonar(int OUTPIN, int INPIN, std::string name)
            : p_trigPin(OUTPIN), p_echoPin(INPIN), p_name(name)
        {
            if(sonar_setup()){std::cout << name << " sonar is online" << std::endl;}
        }

        float read_distance();

    private:
        int p_trigPin;
        int p_echoPin;
        std::string p_name;

        bool sonar_setup();

};