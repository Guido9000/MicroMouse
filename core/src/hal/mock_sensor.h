#pragma once
#include "interfaces.h"

#ifndef ESP_LOGI
#include <iostream>
#define ESP_LOGI(tag, fmt, ...) \
    printf("[%s] " fmt "\n", tag, ##__VA_ARGS__)
#endif

class MockSensor : public IDistanceSensor {
public:
    void  setNextReading(float mm) { reading_ = mm; }
    float getDistanceMM()  const override { return reading_; }
    bool  isWallDetected() const override { return reading_ < 150.0f; }
private:
    float reading_ = 999.0f;
};

class MockMotor : public IMotor {
public:
    void setSpeed(float speed) override {
        ESP_LOGI("MOCK", "Moving forward at %.1f mm/s", speed);
    }
    void stop() override {
        ESP_LOGI("MOCK", "Stop");
    }
    // bool isStalled() const override { return false; }
};