#pragma once

#include <iostream>
// #include "config.h"
// #include "maze.h"
// #include "morse.h"
#include "log.h"

enum Direction {
    NORTH,
    EAST,
    SOUTH,
    WEST
};


struct Position {
    uint8_t   x, y;
    Direction heading;
};


inline Direction rightDirection(Direction heading)
{

    // TODO: Convert in verbose
    std::cout << "Right is " << ((heading + 1) % 4) << std::endl;
    // TODO Blink once
    return static_cast<Direction>((heading + 1) % 4);
}


inline Direction leftDirection(Direction heading)
{

    // TODO: Convert in verbose
    std::cout << "Left is " << ((heading + 3) % 4) << std::endl;
    // TODO Blink three times
    return static_cast<Direction>((heading + 3) % 4);
}


inline Direction backDirection(Direction heading)
{

    // TODO: Convert in verbose
    std::cout << "The opposite direction is " << ((heading + 2) % 4) << std::endl;
    // TODO Blink once long
    return static_cast<Direction>((heading + 2) % 4);
}
