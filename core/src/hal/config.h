#pragma once

// Maths
constexpr float PI = 3.14159f;

// MicroMouse
constexpr float WHEEL_DIAMETER_MM    = 70.0f;
constexpr float WHEEL_BASE_MM        = 90.0f;  // distanza tra le ruote
constexpr float ENCODER_CPR          = 360.0f; // counts per revolution
constexpr float MM_PER_COUNT         = (PI * WHEEL_DIAMETER_MM) / ENCODER_CPR;

// Maze
constexpr uint8_t MAZE_WIDTH         = 16;
constexpr uint8_t MAZE_HEIGHT        = 16;
constexpr float   CELL_SIZE_MM       = 180.0f;
constexpr float   WALL_THICKNESS_MM  = 12.0f;
constexpr float   MAX_WALL_DIST      = 80.0f;   //TODO check

// Control parameters
constexpr float PID_SPEED_KP         = 1.2f;
constexpr float PID_SPEED_KI         = 0.05f;
constexpr float PID_SPEED_KD         = 0.01f;

constexpr float SPEED_EXPLORE_MM_S   = 150.0f;
constexpr float SPEED_SPRINT_MM_S    = 400.0f;