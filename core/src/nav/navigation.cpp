#include <bitset>

#include "navigation.h"
#include "mock_sensor.h"
#include "config.h"
#include "maze.h"
#include "direction.h"


Position Navigation::getPosition() const
{
    return actual_position_;
}


bool Navigation::setPosition(Position new_position)
{
    actual_position_.x = new_position.x;
    actual_position_.y = new_position.y;
    actual_position_.heading = new_position.heading;

    return true;
}


bool Navigation::updateWalls(mazeGrid& maze, const Sonar& front_S, const Sonar& left_S, const Sonar& right_S)
{
    Direction ahead = actual_position_.heading;
    Direction left = leftDirection(actual_position_.heading);
    Direction right = rightDirection(actual_position_.heading);

    if(front_S.thereswall())
    {
        maze.setWall(actual_position_.x, actual_position_.y, ahead);
    }
    if(left_S.thereswall())
    {
        maze.setWall(actual_position_.x, actual_position_.y, left);
    }
    if(right_S.thereswall())
    {
        maze.setWall(actual_position_.x, actual_position_.y, right);
    }
    
    return true;
}