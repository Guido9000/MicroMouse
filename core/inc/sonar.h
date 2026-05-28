#pragma once

#include <iostream>
#include <string>
#include "driver/gpio.h"
#include "esp_timer.h"
#include "esp_adc/adc_oneshot.h"
#include "config.h"
#include "log.h"

extern "C" class Sonar
{ 
    public:
        Sonar() = default;
        explicit Sonar(int OUTPIN, int INPIN, std::string name)
            : p_trigPin(OUTPIN), p_echoPin(INPIN), p_name(name)
        {
            if(sonar_setup()){std::cout << name << " sonar is online" << std::endl;}
        }

        bool theresWall() const;
        float read() const;

    private:
        int p_trigPin;
        int p_echoPin;
        std::string p_name;

        bool sonar_setup();

};


extern "C" class IRSensor
{ 
    public:
        IRSensor() = default;
        explicit IRSensor(adc_channel_t adc_channel, std::string name)
            : p_adc_channel(adc_channel), p_name(name)
        {
            if(irsensor_setup()){std::cout << name << " IR sensor is online" << std::endl;}
        }

        bool theresWall() const;
        float read() const;

    private:
        static adc_oneshot_unit_handle_t adc1_handle;
        static bool adc_initialized;
        adc_channel_t p_adc_channel;
        std::string p_name;
        bool irsensor_setup();

};