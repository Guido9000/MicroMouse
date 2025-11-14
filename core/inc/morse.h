#pragma once

#include <iostream>
#include <map>
#include <string>
#include "driver/gpio.h"

extern const std::map<char, std::string> ascii_to_morse;

//const per non modificare, std::string& msg per passare il riferimento, 
//quindi non genero una copia della stringa originale
void convert_to_morse(const std::string& msg, int led_gate);
void blink_led(const std::string& msg_morse, int led_gate);

extern "C" class MorseLed
{
    //Encapsulation 
    public:
        //constructor             //initializer list
        //explicit è buona prassi metterlo in costruttori con un solo parametro
        //evita conversioni implicite
        explicit MorseLed(int gpio) : gpio_(gpio) {
            gpio_reset_pin((gpio_num_t)gpio_);
            gpio_set_direction((gpio_num_t)gpio_, GPIO_MODE_OUTPUT);
        }

        void dot() const { on(100); }
        void dash() const { on(200); }
        void space() const { off(100); }

    private:
        int gpio_;

        void on(int ms) const;
        void off(int ms) const;
};