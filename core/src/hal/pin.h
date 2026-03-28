#pragma once

// set with idf.py menuconfig
#define BLINK_GPIO   CONFIG_BLINK_GPIO      //
#define BLINK_PERIOD CONFIG_BLINK_PERIOD    //

// Define driver slp
#define MOT_SLP_PIN GPIO_NUM_22
// Define the control inputs
#define MOT_A1_PIN GPIO_NUM_26
#define MOT_A2_PIN GPIO_NUM_14
#define MOT_B1_PIN GPIO_NUM_25
#define MOT_B2_PIN GPIO_NUM_33

// Define the front sensor inputs
#define SEN_TRIG GPIO_NUM_18
#define SEN_ECHO GPIO_NUM_34





// // --- Motori ---
// constexpr uint8_t PIN_MOTOR_L_PWM   = 12;
// constexpr uint8_t PIN_MOTOR_L_DIR_A = 13;
// constexpr uint8_t PIN_MOTOR_L_DIR_B = 14;

// constexpr uint8_t PIN_MOTOR_R_PWM   = 25;
// constexpr uint8_t PIN_MOTOR_R_DIR_A = 26;
// constexpr uint8_t PIN_MOTOR_R_DIR_B = 27;

// // --- Encoder ---
// constexpr uint8_t PIN_ENC_L_A = 34;
// constexpr uint8_t PIN_ENC_L_B = 35;
// constexpr uint8_t PIN_ENC_R_A = 36;
// constexpr uint8_t PIN_ENC_R_B = 39;

// // --- Sensori IR (distanza pareti) ---
// constexpr uint8_t PIN_IR_FRONT_L = 32;
// constexpr uint8_t PIN_IR_FRONT_R = 33;
// constexpr uint8_t PIN_IR_SIDE_L  = 4;
// constexpr uint8_t PIN_IR_SIDE_R  = 5;