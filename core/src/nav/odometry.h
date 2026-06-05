#pragma once

#include <iostream>
#include "config.h"
#include "log.h"


// Estimate physical position
class Odometry
{ 
    public:
        // update values
        void updateSensorLastMeasure(float newMeasure);
        void takeTime(float time);
        void updateSpeed(float speed);
        float wheelSpaceTraveled(float time_, float speed);
        float sensorSpaceTraveled(float oldMeasure_, float newMeasure);
                
    private:
        float oldMeasure_ = 0.0f;
        float startTime_ = 0.0f;
        float speed_ = 0.0f;
};