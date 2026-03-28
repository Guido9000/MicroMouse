////////////// Hardware Abstraction Level //////////////
#pragma once
#include <cstdint>

// Generic interface for distance sensor
class IDistanceSensor {
public:
    virtual ~IDistanceSensor() = default;
    virtual float getDistanceMM() const = 0;
    virtual bool isWallDetected() const = 0;
};

// Generic interface for motor
class IMotor {
public:
    virtual ~IMotor() = default;
    virtual void setSpeed(float speedMMperSec) = 0;
    virtual void stop() = 0;
    // virtual bool isStalled() const = 0; // per motori step
};

// Generic interface for encoder
class IEncoder {
public:
    virtual ~IEncoder() = default;
    virtual int32_t getCount() const = 0;
    virtual float getSpeedMMperSec() const = 0;
    virtual void reset() = 0;
};