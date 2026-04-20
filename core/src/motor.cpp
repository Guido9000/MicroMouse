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


bool Motor::setSpeed(int throttle)
{
    // throttle [0%-100%]
    int duty_cycle = speedToDuty(throttle);
    if(duty_cycle == -99)
    {
        return false;
    }

    gpio_set_level(p_InPin1, duty_cycle > 0 ? 1 : 0); // if (throttle > 0) {1}; else {0}
    gpio_set_level(p_InPin2, duty_cycle < 0 ? 1 : 0);

    // Set PWM duty cycle to control speed
    ledc_set_duty(MOTOR_PWM_MODE, MOTOR_PWM_CHANNEL, duty_cycle);
    ledc_update_duty(MOTOR_PWM_MODE, MOTOR_PWM_CHANNEL);
 
    return true;
}


int Motor::speedToDuty(int throttle) {
    int full_throttle = 100;

    if(speed < 0 || speed > 100) 
    {
        LOG_ERROR("Motor", "Throttle out of range");
        return -99;
    }
    else if(speed = 0)
    {
        return 0;
    }
    return MIN_DUTY_CYCLE + throttle * (MAX_DUTY_CYCLE - MIN_DUTY_CYCLE) / full_throttle;
}


void Motor::testAcceleration()
{
    #define MOTOR_IN1_PIN   GPIO_NUM_22  // IN1 pin connected to motor driver
    #define MOTOR_IN2_PIN   GPIO_NUM_14  // IN2 pin connected to motor driver
    #define MOTOR_ENABLE_PIN GPIO_NUM_26 // Enable pin for PWM control

    // Configure GPIO for motor direction control
    esp_rom_gpio_pad_select_gpio(MOTOR_IN1_PIN);
    gpio_set_direction(MOTOR_IN1_PIN, GPIO_MODE_OUTPUT);
    esp_rom_gpio_pad_select_gpio(MOTOR_IN2_PIN);
    gpio_set_direction(MOTOR_IN2_PIN, GPIO_MODE_OUTPUT);

    // Configure PWM timer
    ledc_timer_config_t pwm_timer = {
        .speed_mode       = MOTOR_PWM_MODE,
        .duty_resolution  = MOTOR_PWM_RES,
        .timer_num        = MOTOR_PWM_TIMER,
        .freq_hz          = MOTOR_PWM_FREQ,
        .clk_cfg          = LEDC_AUTO_CLK
    };
    ledc_timer_config(&pwm_timer);

    // Configure PWM channel
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

    int duty_cycle = 600;   // Minimal duty to run
    int direction = 1;  // 1 for clockwise, 0 for anticlockwise

    while (true) {
        // Set motor direction
        if (direction == 1) {
            gpio_set_level(MOTOR_IN1_PIN, 1);
            gpio_set_level(MOTOR_IN2_PIN, 0);
            printf("Direction: Clockwise\n");
        } else {
            gpio_set_level(MOTOR_IN1_PIN, 0);
            gpio_set_level(MOTOR_IN2_PIN, 1);
            printf("Direction: Anticlockwise\n");
        }

        // Set PWM duty cycle to control speed
        ledc_set_duty(MOTOR_PWM_MODE, MOTOR_PWM_CHANNEL, duty_cycle);
        ledc_update_duty(MOTOR_PWM_MODE, MOTOR_PWM_CHANNEL);

        // Increase the duty cycle for speed control
        duty_cycle += 10; // Increase speed gradually
        printf("Duty Cycle: %d\n", duty_cycle);

        if (duty_cycle > MAX_DUTY_CYCLE) {
            duty_cycle = 1023;  // MAX SPEED

            if (direction == 1) {
                gpio_set_level(MOTOR_IN1_PIN, 1);
                gpio_set_level(MOTOR_IN2_PIN, 0);
                printf("Direction: Clockwise\n");
            } else {
                gpio_set_level(MOTOR_IN1_PIN, 0);
                gpio_set_level(MOTOR_IN2_PIN, 1);
                printf("Direction: Anticlockwise\n");
            }
            vTaskDelay(pdMS_TO_TICKS(1000));

            // Briefly disable motor between direction changes
            gpio_set_level(MOTOR_IN1_PIN, 0);
            gpio_set_level(MOTOR_IN2_PIN, 0);
            vTaskDelay(pdMS_TO_TICKS(100)); // Short delay to stop

            // Reset duty cycle and toggle direction
            duty_cycle = 600;
            direction = !direction;
            printf("Toggling direction\n");
        }

        vTaskDelay(pdMS_TO_TICKS(200)); // Delay for observation
    }
}
