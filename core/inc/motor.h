#pragma once

#include <iostream>
#include <string>
#include "driver/gpio.h"
#include "driver/ledc.h"  // For PWM control
#include "pin.h"
#include "log.h"



extern "C" class Motor
{ 
    public:
        explicit Motor(gpio_num_t InPin1, gpio_num_t InPin2, ledc_channel_t ch1, ledc_channel_t ch2, const std::string& name)
            : p_InPin1(InPin1), p_InPin2(InPin2), ch_in1(ch1), ch_in2(ch2), p_name(name) // initializer list: inizializza direttamente i membri della classe, prima che venga eseguito il corpo del costruttore.
        {
            init_pwm_timer_once();
            setup_gpio();
            setup_pwm(ch_in1, p_InPin1);
            setup_pwm(ch_in2, p_InPin2);
        
            std::cout << "Motor " << name << " is online\n";
        }

        /* Methods */
        bool setSpeed(int throttle);
        void rotate_forward(int throttle);
        void rotate_backward();
        void brake();
        void stop();
        void testAcceleration();
        void printSleepPins();
        void printPins();

    private:    // non voglio che il codice esterno li chiami per sbaglio
        gpio_num_t p_InPin1, p_InPin2;
        ledc_channel_t ch_in1, ch_in2;
        std::string p_name;
        
        static void init_pwm_timer_once();
        bool motor_setup();
        int speedToDuty(int throttle);
        void setup_gpio();
        void setup_pwm(ledc_channel_t ch, int pin);
};