#include "robot.h"

void Robot::init()
{
    solver_ = new RightHandSolver;

    rearAxle_ = Axle(MOT_SLP_PIN, GPIO_NUM_26, GPIO_NUM_14, GPIO_NUM_25, GPIO_NUM_33, "rear");
    frontSensor_ = Sonar(SEN_TRIG, SEN_ECHO, "front");
    // leftSensor_ = Sonar(SEN_TRIG, SEN_ECHO, "left");
    // rightSensor_ = Sonar(SEN_TRIG, SEN_ECHO, "right");
}


bool Robot::explore()
{
    Direction next;
    Position myPosition = navigator_.getPosition();

    // use navigation to find the goal
    while(!maze.isGoal(myPosition.x, myPosition.y)
    {
        next = solver_.nextStep(const mazeGrid& maze, const Position& actual_position);
        rearAxle_.nextMove(next);
        navigator_.setPosition(/* TODO ADJUST NEXT to be Position, not Direction */);
        navigator_.updateWalls(maze, myPosition.x, myPosition.y, myPosition.heading);
    }

    LOG_INFO("Robot", "Exploration is complete")
    return true;
}


bool Robot::sprint()
{
    // read the maze to sprint

    return true;
}


void Robot::rotateByDegrees(float degrees)
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


void Robot::stop()
{

}


void Robot::reachCenter()
{

}


bool Robot::isCentered()
{

    return 0;
}


float Robot::calibrateDist()
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
void Robot::keepEqDistance()
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