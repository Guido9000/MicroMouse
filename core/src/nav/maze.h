#pragma once

#include <iostream>
#include "config.h"
#include "log.h"
#include "direction.h"
#include "navigation.h"

const uint16_t VISITED    = 0x10;
const uint16_t SOLUTION   = 0x20;

struct Position;

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
        bool hasWall(uint8_t x, uint8_t y, Direction dir) const;
        bool isVisited(uint8_t x, uint8_t y) const;
        uint8_t getFlood(uint8_t x, uint8_t y) const;
        void setFlood(uint8_t x, uint8_t y, uint8_t value);
        bool isBoarder(uint8_t x, uint8_t y, Direction dir) const;
        Position adiacentCell(uint8_t x, uint8_t y, Direction dir) const;
        bool isGoal(uint8_t x, uint8_t y) const;
        void printCellState(uint8_t x, uint8_t y);


    private:    // non voglio che il codice esterno li chiami per sbaglio
        maze_cell cells_[256];  //16*16
        uint8_t index(uint8_t x, uint8_t y) const; // const promette: non tocco nulla
        void setWallCell(uint8_t x, uint8_t y, Direction dir);
        bool setNeighbor(uint8_t x, uint8_t y, Direction dir);
        void setVisited(uint8_t x, uint8_t y);
};
