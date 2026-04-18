#include <bitset>

#include "navigation.h"
#include "mock_sensor.h"
#include "config.h"

Direction Navigation::turnRight(Direction heading)
{

    // TODO: Convert in verbose
    std::cout << "Right is " << ((heading + 1) % 4) << std::endl;
    // TODO Blink once
    return static_cast<Direction>((heading + 1) % 4);
}


Direction Navigation::turnLeft(Direction heading)
{

    // TODO: Convert in verbose
    std::cout << "Left is " << ((heading + 3) % 4) << std::endl;
    // TODO Blink three times
    return static_cast<Direction>((heading + 3) % 4);
}


Direction Navigation::turnBack(Direction heading)
{

    // TODO: Convert in verbose
    std::cout << "The opposite direction is " << ((heading + 2) % 4) << std::endl;
    // TODO Blink once long
    return static_cast<Direction>((heading + 2) % 4);
}


void Navigation::rotateByDegrees(float degrees)
{
    if(degrees > 0)
    {
        // applica spinta positiva a motore dx
        // applica spinta negativa a motore sx
        // stop
    }
    else if(degrees < 0)
    {
        // applica spinta positiva a motore sx
        // applica spinta negativa a motore dx
        // stop
    }
}


void Navigation::stop()
{

}


void Navigation::reachCenter()
{

}


bool Navigation::isCentered()
{

    return 0;
}


float Navigation::calibrateDist()
{
    MockSensor frontSensor;
    if(isCentered() == 1)
    {
        frontSensor.getDistanceMM();
        //TODO: Correct distance. Go to proper center
    }

    return 0;
}

//Center the robot in the cell to keep same distance from left and right
void Navigation::keepEqDistance()
{
    // Possible first approach:
    // 1) rileva differenza dx vs sx
    // 2) applica rotazione verso centro
    // 3) avanza fino a rendere dx = sx
    // 4) applica anti rotazione

    // TODO: left and right sensor must be passed from the extern
    MockSensor leftSensor, rightSensor;
    float gap;
    float leftWheelSpeed;
    float rightWheelSpeed;
    float normConst;

    normConst = leftSensor.getDistanceMM() + rightSensor.getDistanceMM();
    gap = leftSensor.getDistanceMM() - rightSensor.getDistanceMM();

    if(leftSensor.isWallDetected() && rightSensor.isWallDetected())
    {
        if(abs(gap) > 5.0)
        {
            if(gap > 0)
            {
                rotateByDegrees(-45.0);
                // Go ahead until gap = 0; (reachCenter?)
                rotateByDegrees(45.0);

                // TODO
                // Dynamic algorithm
                // Reduce right wheel speed
                // rightWheelSpeed = 0.2 * gap / normConst;
            }
            else
            {
                rotateByDegrees(45.0);
                // Go ahead until gap = 0;
                rotateByDegrees(-45.0);
                
                // TODO
                // Dynamic algorithm
                // Reduce left wheel speed
                // leftWheelSpeed = 0.2 * gap / normConst;
            }
        }
    }
} 