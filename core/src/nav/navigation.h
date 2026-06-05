#pragma once

#include <iostream>
#include "config.h"
#include "maze.h"
// #include "morse.h"
#include "log.h"
#include "sensor.h"
#include "direction.h"
#include "mock_sensor.h"

struct Position;
class mazeGrid;
class UsSensor; 

// posizione, aggiornamento pareti
class Navigation
{ 
    public:
        bool setPosition(Position new_position);
        bool setHeading(Position new_position);
        Position getPosition() const;

        bool updateWalls(mazeGrid& maze, const UsSensor& front_S, const IRSensor& left_S, const IRSensor& right_S);

    private:
        Position actual_position_ = {.x = 0 , .y = 0, .heading = NORTH};
};
