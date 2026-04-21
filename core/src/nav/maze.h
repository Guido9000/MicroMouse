#pragma once

#include <iostream>
#include "config.h"
#include "log.h"
#include "direction.h"

const uint16_t VISITED    = 0x10;
const uint16_t SOLUTION   = 0x20;

struct maze_cell
{ 
    uint8_t walls = {0};
    uint8_t floods = {0};
};

// struttura dati labirinto
extern "C" class mazeGrid
{ 
    public:
        void setWall(uint8_t x, uint8_t y, Direction dir);
        bool isVisited(uint8_t x, uint8_t y) const;
        uint8_t getFlood(uint8_t x, uint8_t y) const;
        void setFlood(uint8_t x, uint8_t y, uint8_t value);

        void printCellState(uint8_t x, uint8_t y);


    private:    // non voglio che il codice esterno li chiami per sbaglio
        maze_cell cells_[256];  //16*16
        uint8_t index(uint8_t x, uint8_t y) const; // const promette: non tocco nulla
        bool isGoal(uint8_t x, uint8_t y) const;
        bool isBoarder(uint8_t x, uint8_t y, Direction dir) const;
        bool hasWall(uint8_t x, uint8_t y, Direction dir) const;
        void setWallCell(uint8_t x, uint8_t y, Direction dir);
        bool setNeighbor(uint8_t x, uint8_t y, Direction dir);
        bool isVisited(uint8_t x, uint8_t y) const;
        void setVisited(uint8_t x, uint8_t y);
};
