#pragma once

#include <iostream>
#include "config.h"
#include "maze.h"
// #include "morse.h"
#include "log.h"

struct Position {
    uint8_t   x, y;
    Direction heading;
};

extern "C" class Navigation
{ 
    public:
        Direction turnRight(Direction heading);
        Direction turnLeft(Direction heading);
        Direction turnBack(Direction heading);
        void rotateByDegrees(float degrees);
        void stop();
        void reachCenter();
        bool isCentered();
        float calibrateDist();
        void keepEqDistance();

    private:    // non voglio che il codice esterno li chiami per sbaglio
        Position actual_position_ = {0 , 0, NORTH};
};
