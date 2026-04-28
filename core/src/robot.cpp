#include "robot.h"


bool Robot::test()
{
    // rearAxle_.rotate_forward();
    std::cout << "Chiappette: " << frontSensor_.read() << std::endl;
    if(!frontSensor_.theresWall())
    {
        std::cout << "free space" << std::endl;
        rearAxle_.move_forward(frontSensor_.read());
    }
    else
    {
        std::cout << "wall" << std::endl;
        rearAxle_.stop();
    }

    return true;
}


bool Robot::explore()
{
    float time = 0; // TODO substitute with clock
    float speed = 0; // TODO substitute speed
    Direction next;
    Position myPosition = navigator_.getPosition();

    // get centered in (0,0)
    if(initializePosition())
    {
        // use navigation to find the goal
        while(!maze_.isGoal(myPosition.x, myPosition.y))
        {
            // Orient robot direction
            /* FRECCINA!!!! */
            next = solver_->nextStep(maze_, myPosition); // next is the rotation to perform
            rearAxle_.prepareNextMove(next); // rotate
            navigator_.setHeading(myPosition); //update heading

            // Initialize odometry
            odometry_.takeTime(time); // inizializza cronometro per odometria ruote
            odometry_.updateSensorLastMeasure(frontSensor_.read()); // initialize front sensor for odometry

            // Move ahead
            rearAxle_.move_forward(100); // Move forward into next corridor
            // rearAxle_.nextCenterReached(); // Probably useless, substituted with odometry

            // Almost reaching the next center cell: update navigation position and set walls
            if(odometry_.wheelSpaceTraveled(time, speed) >= CELL_SIZE_MM * 0.9)
            {
                if(!maze_.isBoarder(myPosition.x, myPosition.y, myPosition.heading))
                {    
                    navigator_.setPosition(maze_.adiacentCell(myPosition.x, myPosition.y, myPosition.heading));  // update navigation position
                }
                else
                {
                    LOG_ERROR("Position", "I cannot go beyond the border");
                }
                navigator_.updateWalls(maze_, frontSensor_, leftSensor_, rightSensor_);
                /* TODO FRECCINE! */
                next = solver_->nextStep(maze_, myPosition); // be prepared for next action
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

    LOG_INFO("Robot", "Exploration is complete");
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


bool Robot::nextCenterReached()
{
    double spaceTraveled = 0;
    float time = 0;     // TODO Pass speed through the function
    float speed = 0;    // TODO Pass speed through the function

    std::cout << "TEST DISTANZA" << static_cast<int> (odometry_.wheelSpaceTraveled(time, speed)) << " " << odometry_.wheelSpaceTraveled(time, speed) << std::endl;
    int tmp = static_cast<int> (odometry_.wheelSpaceTraveled(time, speed));

    while(spaceTraveled > (tmp % 180))
    {
        spaceTraveled = (tmp % 180);
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
    /* TODO adapt MockSensor for Sonar */
    // MockSensor frontSensor;
    // if(isCentered() == 1)
    // {
    //     frontSensor.getDistanceMM();
    //     //TODO: Correct distance. Go to proper center
    // }

    return 0.0f;
}

//Center the robot in the cell to keep same distance from left and right
void Robot::keepEqDistance()
{
    // Possible first approach:
    // 1) rileva differenza dx vs sx
    // 2) applica rotazione verso centro
    // 3) avanza fino a rendere dx = sx
    // 4) applica anti rotazione

    /* TODO: MockSensor leftSensor_, rightSensor_;
        e` scritto per Mocksensor, va sistemato per Sonar*/
    // // TODO: left and right sensor must be passed from the extern
    // // MockSensor
    // MockSensor leftSensor_, rightSensor_;
    // float gap;
    // float leftWheelSpeed;
    // float rightWheelSpeed;
    // float normConst;

    // normConst = leftSensor_.getDistanceMM() + rightSensor_.getDistanceMM();
    // gap = leftSensor_.getDistanceMM() - rightSensor_.getDistanceMM();

    // if(leftSensor_.isWallDetected() && rightSensor_.isWallDetected())
    // {
    //     if(abs(gap) > 5.0)
    //     {
    //         if(gap > 0)
    //         {
    //             rotateByDegrees(-45.0);
    //             // Go ahead until gap = 0; (reachCenter?)
    //             rotateByDegrees(45.0);

    //             // TODO
    //             // Dynamic algorithm
    //             // Reduce right wheel speed
    //             // rightWheelSpeed = 0.2 * gap / normConst;
    //         }
    //         else
    //         {
    //             rotateByDegrees(45.0);
    //             // Go ahead until gap = 0;
    //             rotateByDegrees(-45.0);
                
    //             // TODO
    //             // Dynamic algorithm
    //             // Reduce left wheel speed
    //             // leftWheelSpeed = 0.2 * gap / normConst;
    //         }
    //     }
    // }
} 