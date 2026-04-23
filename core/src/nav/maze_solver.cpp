#include "maze_solver.h"
#include "maze.h"
#include "navigation.h"



// Given a position in the maze, get the next move following the righthand rule
Direction RightHandSolver::nextStep(const mazeGrid& maze, const Position& actual_position)
{
    Navigation nav;
    Direction actual_direction = actual_position.heading;

    Direction right   = nav.turnRight(actual_direction);
    Direction forward = actual_direction;
    Direction left    = nav.turnLeft(actual_direction);
    Direction back    = nav.turnBack(actual_direction);


    // Turn right if possible
    if(!maze.hasWall(actual_position.x, actual_position.y, right))
    {
        return right;
    }
    // Go straight if possible
    else if(!maze.hasWall(actual_position.x, actual_position.y, forward))
    {
        return forward;
    }
    // Turn left if possible
    else if(!maze.hasWall(actual_position.x, actual_position.y, left))
    {
        return left;
    }
    // Blind spot, go back
    else
    {
        if(!maze.hasWall(actual_position.x, actual_position.y, back))
        {
            return back;
        }
        else
        {
            LOG_ERROR("Solver", "I'm lost in a blind spot without exit");
            // TODO Blink SOS
            exit(1);
        }
    }
}