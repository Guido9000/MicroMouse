#pragma once

#include <iostream>
#include "config.h"
#include "log.h"

// enum Direction {
//     NORTH  = 1 << 0,
//     SOUTH   = 1 << 1,
//     WEST = 1 << 2,
//     EAST   = 1 << 3
// };
enum Direction {
    NORTH,
    EAST,
    SOUTH,
    WEST
};
const uint16_t VISITED    = 0x10;
const uint16_t SOLUTION   = 0x20;

struct maze_cell
{ 
    uint8_t walls = {0};
    uint8_t floods = {0};
};

extern "C" class maze_grid
{ 
    public:
        bool hasWall(uint8_t x, uint8_t y, Direction dir) const;
        void setWall(uint8_t x, uint8_t y, Direction dir);
        void setWallCell(uint8_t x, uint8_t y, Direction dir);
        bool setNeighbor(uint8_t x, uint8_t y, Direction dir);
        bool isVisited(uint8_t x, uint8_t y) const;
        void setVisited(uint8_t x, uint8_t y);
        uint8_t getFlood(uint8_t x, uint8_t y) const;
        void setFlood(uint8_t x, uint8_t y, uint8_t value);
        bool isGoal(uint8_t x, uint8_t y) const;
        void print(uint8_t x, uint8_t y);
        Direction opposite_dir(Direction dir);

    private:    // non voglio che il codice esterno li chiami per sbaglio
        maze_cell cells_[256];  //16*16
        uint8_t index(uint8_t x, uint8_t y) const; // const promette: non tocco nulla
};
