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

    // get centered in (0,0)
    if(initializePosition())
    {
        // use navigation to find the goal
        while(!maze.isGoal(myPosition.x, myPosition.y)
        {
            // Orient robot direction
            next = solver_.nextStep(maze, myPosition); // next is the rotation to perform
            rearAxle_.prepareNextMove(next); // rotate
            navigator_.setHeading(myPosition); //update heading

            // Initialize odometry
            odometry_.takeTime(); // inizializza cronometro per odometria ruote
            odometry_.updateSensorLastMeasure(frontSensor_.read()); // initialize front sensor for odometry

            // Move ahead
            rearAxle_.move_forward() // Move forward into next corridor
            rearAxle_.nextCenterReached(); // 

            // Almost reaching the next center cell: update navigation position and set walls
            if(odometry_.wheelSpaceTraveled(time, speed) >= CELL_SIZE_MM * 0.9)
            {
                if(!maze.isBoarder(myPosition.x, myPosition.y, myPosition.heading))
                {    
                    navigator_.setPosition(maze.adiacentCell(myPosition));  // update navigation position
                }
                else
                {
                    LOG_ERROR("Position", "I cannot go beyond the border");
                }
                navigator_.updateWalls(maze, myPosition.x, myPosition.y, myPosition.heading);
                next = solver_.nextStep(maze, actual_position); // be prepared for next action
            }

            // Reach next center cell with wheelSpaceTraveled(time, speed) = CELL_SIZE_MM and iterate the while loop
            if(odometry_.wheelSpaceTraveled(time, speed) >= CELL_SIZE_MM)
            {
                // if turn available/necessary, be ready to stop
                if (myPosition.heading != next)
                {
                    //stop, next iteration you'll turn
                    rearAxle_.stop();
                }
                // else go stright without stopping
                else
                {
                    continue;
                }
            }

        }
    }
    else
    {
        LOG_ERROR("Position", "Initialization position (0,0) failed");
        return false;
    }

    LOG_INFO("Robot", "Exploration is complete")
    return true;
}


bool Robot::sprint()
{
    // read the maze to sprint

    return true;
}


bool Robot::initializePosition()
{
    // Verify to be in a blind spot
    // Center in the cell
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


bool Robot::nextCenterReached()
{
    double spaceTraveled = 0;

    while(spaceTraveled > (odometry_.wheelSpaceTraveled(time, speed) % 180.0f))
    {
        spaceTraveled = (odometry_.wheelSpaceTraveled(time, speed) % 180.0f)
        return false;
    }
    return true;
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