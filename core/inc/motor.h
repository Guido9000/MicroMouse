#pragma once

#include <iostream>
#include <string>
#include "driver/gpio.h"
#include "driver/ledc.h"  // For PWM control
#include "pin.h"

extern "C" class Motor
{ 
    public:
        explicit Motor(int InPin1, int InPin2, const std::string& name)
            : p_InPin1(InPin1), p_InPin2(InPin2), p_name(name) // initializer list: inizializza direttamente i membri della classe, prima che venga eseguito il corpo del costruttore.
        {
            if(motor_setup()){std::cout << "Motor " << name << " is online" << std::endl;}

            // GPIO setup
            esp_rom_gpio_pad_select_gpio(InPin1);
            gpio_set_direction(InPin1, GPIO_MODE_OUTPUT);
            esp_rom_gpio_pad_select_gpio(InPin2);
            gpio_set_direction(InPin2, GPIO_MODE_OUTPUT);

            // PWM timer and channel
            ledc_timer_config_t pwm_timer = {
                .speed_mode       = MOTOR_PWM_MODE,
                .duty_resolution  = MOTOR_PWM_RES,
                .timer_num        = MOTOR_PWM_TIMER,
                .freq_hz          = MOTOR_PWM_FREQ,
                .clk_cfg          = LEDC_AUTO_CLK
            };
            ledc_timer_config(&pwm_timer);

            ledc_channel_config_t pwm_channel = {
                .gpio_num       = MOTOR_ENABLE_PIN,
                .speed_mode     = MOTOR_PWM_MODE,
                .channel        = MOTOR_PWM_CHANNEL,
                .intr_type      = LEDC_INTR_DISABLE,
                .timer_sel      = MOTOR_PWM_TIMER,
                .duty           = 0,
                .hpoint         = 0
            };
            ledc_channel_config(&pwm_channel);
        }

        int speedToDuty(int throttle)
        bool setSpeed(int throttle);
        void stop();
        void testAcceleration();

    private:    // non voglio che il codice esterno li chiami per sbaglio
        int p_InPin1;
        int p_InPin2;
        std::string p_name;
        
        bool motor_setup();
};