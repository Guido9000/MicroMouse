#pragma once

#include <iostream>
#include "config.h"
#include "maze.h"
// #include "morse.h"
#include "log.h"
#include "sonar.h"
#include "direction.h"
#include "mock_sensor.h"

struct Position;
class mazeGrid;
class Sonar; 

// posizione, aggiornamento pareti
extern "C" class Navigation
{ 
    public:
        bool setPosition(Position new_position);
        bool setHeading(Position new_position);
        Position getPosition() const;

        bool updateWalls(mazeGrid& maze, const Sonar& front_S, const Sonar& left_S, const Sonar& right_S);

    private:
        Position actual_position_ = {.x = 0 , .y = 0, .heading = NORTH};
};
