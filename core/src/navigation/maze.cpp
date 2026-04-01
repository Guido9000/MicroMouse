#include <bitset>
#include <iostream>
#include "hal/config.h"
#include "../src/navigation/maze.h"

using namespace std;

// uint8_t getFlood(uint8_t x, uint8_t y);
// void setFlood(uint8_t x, uint8_t y, uint8_t value);

uint8_t maze_grid::index(uint8_t x, uint8_t y) const
{
    std::cout << "Cell coordinates (" << int(x) << "," << int(y) << ") -> ";
    std::cout << "cell index: " << x * MAZE_WIDTH + y << std::endl;

    return y * MAZE_WIDTH + x;
}


bool maze_grid::hasWall(uint8_t x, uint8_t y, Direction dir)
{
    maze_cell& tmp_cell = cells_[index(x,y)];

    if(tmp_cell.walls &= dir)   //TODO: convert dir into the correct string
    {
        LOG_VERBOSE("Maze", "There is a wall in that direction");
        return 1;
    }

    LOG_VERBOSE("Maze", "There is no wall in that direction");
    return 0;
}


void maze_grid::setWall(uint8_t x, uint8_t y, Direction dir)
{
    maze_cell& tmp_cell = cells_[index(x,y)];

    tmp_cell.walls |= dir;
    LOG_VERBOSE("Maze", "The wall is set");
}


bool maze_grid::isVisited(uint8_t x, uint8_t y)
{
    maze_cell& tmp_cell = cells_[index(x,y)];

    if(tmp_cell.walls &= VISITED){
        LOG_VERBOSE("Maze", "The cell was already visited");
        return 1;
    }

    LOG_VERBOSE("Maze", "The cell is not visited already");
    return 0;
}


void maze_grid::setVisited(uint8_t x, uint8_t y)
{
    maze_cell& tmp_cell = cells_[index(x,y)];

    tmp_cell.walls |= VISITED;
    LOG_VERBOSE("Maze", "The cell is now visited");

}


void maze_grid::print(uint8_t x, uint8_t y)
{
    maze_cell tmp_cell = cells_[index(x,y)];

    cout << "Walls in the cell: " << bitset<8>(tmp_cell.walls) << endl;
    cout << "Floods of the cell: " << bitset<8>(tmp_cell.floods) << endl;
}