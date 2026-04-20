#include "robot.h"

float calculateRotation(const Direction OldDir, const Direction NewDir)
{
    float degrees = 0.0;

    for(int i = 0; i < 4; i++)
    {
        if (NewDir == ((OldDir + i) % 4))
        {
            break;
        }
        degrees += 90.0;
    }
    if (degrees > 180.0)
    {
        degrees = (degrees - 360.0);
    }

    return degrees;
}


bool Robot::e_turn(const float degrees)
{

    if(degrees > 0)
    {
        // turn right
    }
    else if(degrees < 0)
    {
        // turn left
    }
    
    // Send command and detach (Switch on left engine +1 && switch on right engine -1)
    // Count time (Wait the proper time to get corresponding degrees turn)
    // Stop engines (+ semaphore?)

    // Maneuver completed
    return 1;
}


bool Robot::e_goAhead()
{
    // Send command and detach (Switch on left engine +1 && switch on right engine +1)
    // Count time (Calculate distance to cover the space from center to center of cells)
    // Stop engines (+ semaphore?)

    // Maneuver completed
    return 1;
}