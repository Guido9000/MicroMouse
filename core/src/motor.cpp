#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "motor.h"


void Motor::setup_gpio()
{
    gpio_reset_pin((gpio_num_t)p_InPin1);
    gpio_set_direction((gpio_num_t)p_InPin1, GPIO_MODE_OUTPUT);

    gpio_reset_pin((gpio_num_t)p_InPin2);
    gpio_set_direction((gpio_num_t)p_InPin2, GPIO_MODE_OUTPUT);

    gpio_set_level((gpio_num_t)p_InPin1, 0);
    gpio_set_level((gpio_num_t)p_InPin2, 0);
}


void Motor::init_pwm_timer_once()
{
    static bool initialized = false;

    if (initialized) return;

    ledc_timer_config_t pwm_timer = {};
    pwm_timer.speed_mode      = MOTOR_PWM_MODE;
    pwm_timer.duty_resolution = MOTOR_PWM_RES;
    pwm_timer.timer_num       = MOTOR_PWM_TIMER;
    pwm_timer.freq_hz         = MOTOR_PWM_FREQ;
    pwm_timer.clk_cfg         = LEDC_AUTO_CLK;

    ledc_timer_config(&pwm_timer);

    initialized = true;
}


void Motor::setup_pwm(ledc_channel_t ch, int pin)
{
    ledc_channel_config_t pwm_channel = {};
    pwm_channel.gpio_num   = pin;
    pwm_channel.speed_mode = MOTOR_PWM_MODE;
    pwm_channel.channel    = ch;
    pwm_channel.timer_sel  = MOTOR_PWM_TIMER;
    pwm_channel.intr_type  = LEDC_INTR_DISABLE;
    pwm_channel.duty       = 0;
    pwm_channel.hpoint     = 0;

    ledc_channel_config(&pwm_channel);
}


void Motor::rotate_forward(int throttle)
{
    int duty_cycle = speedToDuty(throttle);

        std::cout << "throttle: " << throttle << " duty: " << duty_cycle << std::endl;

        // Set PWM duty cycle to control speed
        ledc_set_duty(MOTOR_PWM_MODE, ch_in1, duty_cycle);
        ledc_update_duty(MOTOR_PWM_MODE, ch_in1);

        ledc_set_duty(MOTOR_PWM_MODE, ch_in2, 0);
        ledc_update_duty(MOTOR_PWM_MODE, ch_in2);

}


void Motor::rotate_backward()
{
    // copy rotate_forward()
}


void Motor::brake()
{
    ledc_set_duty(MOTOR_PWM_MODE, ch_in1, MAX_DUTY_CYCLE);
    ledc_set_duty(MOTOR_PWM_MODE, ch_in2, MAX_DUTY_CYCLE);

    ledc_update_duty(MOTOR_PWM_MODE, ch_in1);
    ledc_update_duty(MOTOR_PWM_MODE, ch_in2);
}


void Motor::stop()
{
    ledc_set_duty(MOTOR_PWM_MODE, ch_in1, 0);
    ledc_set_duty(MOTOR_PWM_MODE, ch_in2, 0);

    ledc_update_duty(MOTOR_PWM_MODE, ch_in1);
    ledc_update_duty(MOTOR_PWM_MODE, ch_in2);
}


bool Motor::setSpeed(int throttle)
{
    // // throttle [0%-100%]
    // int duty_cycle = speedToDuty(throttle);

    // gpio_set_level(p_InPin1, duty_cycle > 0 ? 1 : 0); // if (throttle > 0) {1}; else {0}
    // gpio_set_level(p_InPin2, duty_cycle < 0 ? 1 : 0);

    // // Set PWM duty cycle to control speed
    // ledc_set_duty(MOTOR_PWM_MODE, MOTOR_PWM_CHANNEL, duty_cycle);
    // ledc_update_duty(MOTOR_PWM_MODE, MOTOR_PWM_CHANNEL);
 
    return true;
}


// convert throttle in PWM signal
int Motor::speedToDuty(int throttle)
{
    int full_throttle = 100;

    // Keep range [0 - full_throttle]
    if(throttle < 0)
    {
        throttle = 0;
    }
    else if(throttle > 100)
    {
        throttle = 100;
    }

    return MIN_DUTY_CYCLE + throttle * (MAX_DUTY_CYCLE - MIN_DUTY_CYCLE) / full_throttle;
}


// void Motor::testAcceleration()
// {
//     #define MOTOR_IN1_PIN   GPIO_NUM_22  // IN1 pin connected to motor driver
//     #define MOTOR_IN2_PIN   GPIO_NUM_14  // IN2 pin connected to motor driver
//     #define MOTOR_ENABLE_PIN GPIO_NUM_26 // Enable pin for PWM control

//     // Configure GPIO for motor direction control
//     esp_rom_gpio_pad_select_gpio(MOTOR_IN1_PIN);
//     gpio_set_direction(MOTOR_IN1_PIN, GPIO_MODE_OUTPUT);
//     esp_rom_gpio_pad_select_gpio(MOTOR_IN2_PIN);
//     gpio_set_direction(MOTOR_IN2_PIN, GPIO_MODE_OUTPUT);

//     // Configure PWM timer
//     ledc_timer_config_t pwm_timer = {};
//         pwm_timer.speed_mode       = MOTOR_PWM_MODE;
//         pwm_timer.duty_resolution  = MOTOR_PWM_RES;
//         pwm_timer.timer_num        = MOTOR_PWM_TIMER;
//         pwm_timer.freq_hz          = MOTOR_PWM_FREQ;
//         pwm_timer.clk_cfg          = LEDC_AUTO_CLK;
//     ledc_timer_config(&pwm_timer);

//     // Configure PWM channel
//     ledc_channel_config_t pwm_channel = {};
//         pwm_channel.gpio_num       = MOTOR_ENABLE_PIN;
//         pwm_channel.speed_mode     = MOTOR_PWM_MODE;
//         // pwm_channel.channel        = MOTOR_PWM_CHANNEL;
//         pwm_channel.intr_type      = LEDC_INTR_DISABLE;
//         pwm_channel.timer_sel      = MOTOR_PWM_TIMER;
//         pwm_channel.duty           = 0;
//         pwm_channel.hpoint         = 0;
//     ledc_channel_config(&pwm_channel);

//     int duty_cycle = 600;   // Minimal duty to run
//     int direction = 1;  // 1 for clockwise, 0 for anticlockwise

//     while (true) {
//         // Set motor direction
//         if (direction == 1) {
//             gpio_set_level(MOTOR_IN1_PIN, 1);
//             gpio_set_level(MOTOR_IN2_PIN, 0);
//             printf("Direction: Clockwise\n");
//         } else {
//             gpio_set_level(MOTOR_IN1_PIN, 0);
//             gpio_set_level(MOTOR_IN2_PIN, 1);
//             printf("Direction: Anticlockwise\n");
//         }

//         // Set PWM duty cycle to control speed
//         ledc_set_duty(MOTOR_PWM_MODE, MOTOR_PWM_CHANNEL, duty_cycle);
//         ledc_update_duty(MOTOR_PWM_MODE, MOTOR_PWM_CHANNEL);

//         // Increase the duty cycle for speed control
//         duty_cycle += 10; // Increase speed gradually
//         printf("Duty Cycle: %d\n", duty_cycle);

//         if (duty_cycle > MAX_DUTY_CYCLE) {
//             duty_cycle = 1023;  // MAX SPEED

//             if (direction == 1) {
//                 gpio_set_level(MOTOR_IN1_PIN, 1);
//                 gpio_set_level(MOTOR_IN2_PIN, 0);
//                 printf("Direction: Clockwise\n");
//             } else {
//                 gpio_set_level(MOTOR_IN1_PIN, 0);
//                 gpio_set_level(MOTOR_IN2_PIN, 1);
//                 printf("Direction: Anticlockwise\n");
//             }
//             vTaskDelay(pdMS_TO_TICKS(1000));

//             // Briefly disable motor between direction changes
//             gpio_set_level(MOTOR_IN1_PIN, 0);
//             gpio_set_level(MOTOR_IN2_PIN, 0);
//             vTaskDelay(pdMS_TO_TICKS(100)); // Short delay to stop

//             // Reset duty cycle and toggle direction
//             duty_cycle = 600;
//             direction = !direction;
//             printf("Toggling direction\n");
//         }

//         vTaskDelay(pdMS_TO_TICKS(200)); // Delay for observation
//     }
// }


void Motor::printSleepPins()
{
    std::cout << "Driver sleep pin: " << MOT_SLP_PIN << std::endl;
}

void Motor::printPins()
{
    std::cout << "Motor: " << p_name << ", pin 1: " << p_InPin1 << ", pin 2: " << p_InPin2 << std::endl;
}