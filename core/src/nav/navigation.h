#pragma once

#include <iostream>
#include "config.h"
#include "maze.h"
// #include "morse.h"
#include "log.h"
#include "sonar.h"

struct Position {
    uint8_t   x, y;
    Direction heading;
};

// posizione, aggiornamento pareti
extern "C" class Navigation
{ 
    public:
        bool setPosition(Position new_position);
        Position getPosition() const;

        bool updateWalls(mazeGrid& maze, const Sonar& front_S, const Sonar& left_S, const Sonar& right_S);

    private:    // non voglio che il codice esterno li chiami per sbaglio
        Position actual_position_ = {0 , 0, NORTH};
};
