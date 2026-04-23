#include "odometry.h"


// Measured speed at full battery capacity * CPU clock
float Odometry::wheelSpaceTraveled(float time, float speed)
{
    float distanceTraveled = speed_ * (time - startTime_);

    // if change of speed, return distance
    if(speed != speed_)
    {
        updateSpeed(speed);
        takeTime(time);
        return distanceTraveled;
    }
    
    return distanceTraveled;
}


// TODO connect to CPU clock
void Odometry::takeTime(float time)
{
    startTime_ = time;
}


void Odometry::updateSpeed(float speed)
{
    speed_ = speed;
}


float Odometry::sensorSpaceTraveled(float oldMeasure_, float newMeasure)
{
    float distanceTraveled = oldMeasure_ - newMeasure;
    updateSensorLastMeasure(newMeasure);

    return distanceTraveled;
}


void Odometry::updateSensorLastMeasure(float newMeasure)
{
    oldMeasure_ = newMeasure;
}