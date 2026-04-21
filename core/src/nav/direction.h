#pragma once

#include <iostream>
#include "config.h"
#include "maze.h"
// #include "morse.h"
#include "log.h"

enum Direction {
    NORTH,
    EAST,
    SOUTH,
    WEST
};

// posizione, aggiornamento pareti
extern "C" class navigationDirection
{ 
    public:
        Direction rightDirection(Direction heading);
        Direction leftDirection(Direction heading);
        Direction backDirection(Direction heading);

};
