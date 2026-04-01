#pragma once

#include <iostream>
#include "hal/config.h"
#include "../../inc/log.h"

enum Direction {
    NORD  = 1 << 0,
    SUD   = 1 << 1,
    OVEST = 1 << 2,
    EST   = 1 << 3
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
        bool hasWall(uint8_t x, uint8_t y, Direction dir);
        void setWall(uint8_t x, uint8_t y, Direction dir);
        bool isVisited(uint8_t x, uint8_t y);
        void setVisited(uint8_t x, uint8_t y);
        uint8_t getFlood(uint8_t x, uint8_t y);
        void setFlood(uint8_t x, uint8_t y, uint8_t value);
        // maze_cell& getCell(uint8_t x, uint8_t y);
        void print(uint8_t x, uint8_t y);

    private:    // non voglio che il codice esterno li chiami per sbaglio
        maze_cell cells_[256];  //16*16
        uint8_t index(uint8_t x, uint8_t y) const; // const promette: non tocco nulla
};
