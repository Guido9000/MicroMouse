#include <bitset>

#include "config.h"
#include "maze.h"
#include "log.h"

using namespace std;

// uint8_t getFlood(uint8_t x, uint8_t y);
// void setFlood(uint8_t x, uint8_t y, uint8_t value);

uint8_t maze_grid::index(uint8_t x, uint8_t y) const
{
    // TODO: Convert in verbose
    std::cout << "Cell coordinates (" << int(x) << "," << int(y) << ") -> ";
    std::cout << "cell index: " << x * MAZE_WIDTH + y << std::endl;

    return y * MAZE_WIDTH + x;
}


Direction maze_grid::opposite_dir(Direction dir){
    if(dir == NORTH){
        dir = SOUTH;
    }
    else if(dir == SOUTH){
        dir = NORTH;
    }
    else if(dir == EAST){
        dir = WEST;
    }
    else if(dir == WEST){
        dir = EAST;
    }

    return dir;
}


bool maze_grid::hasWall(uint8_t x, uint8_t y, Direction dir) const
{
    const maze_cell& tmp_cell = cells_[index(x,y)];

    if(tmp_cell.walls & (1 << dir))   //TODO: convert dir into the correct string
    {
        LOG_VERBOSE("Maze", "There is a wall in that direction");
        return 1;
    }

    LOG_VERBOSE("Maze", "There is no wall in that direction");
    return 0;
}


void maze_grid::setWall(uint8_t x, uint8_t y, Direction dir)
{
    setWallCell(x, y, dir);
    setNeighbor(x, y, dir);
}


void maze_grid::setWallCell(uint8_t x, uint8_t y, Direction dir)
{
    maze_cell& tmp_cell = cells_[index(x,y)];

    tmp_cell.walls |= (1 << dir);

    cout << "Walls in the cell: " << bitset<8>(tmp_cell.walls) << endl;
    LOG_VERBOSE("Maze", "The wall is set");
}

bool maze_grid::setNeighbor(uint8_t x, uint8_t y, Direction dir)
{
    if(dir == NORTH && x != 0){
        x = x - 1;
    }
    else if(dir == SOUTH && x != 15){
        x = x + 1;
    }
    else if(dir == WEST && y != 0){
        y = y - 1;
    }
    else if(dir == EAST && x != 15){
        y = y + 1;
    }
    else{
        return 0;
    }

    dir = opposite_dir(dir);
    setWallCell(x, y, dir);

    LOG_VERBOSE("Maze", "The wall in the neighbor cell is set");
    return 1;
}

bool maze_grid::isVisited(uint8_t x, uint8_t y) const
{
    const maze_cell& tmp_cell = cells_[index(x,y)];

    if(tmp_cell.walls & VISITED){
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


// Define goal at the center of the maze
bool maze_grid::isGoal(uint8_t x, uint8_t y) const {
    return (x == MAZE_WIDTH/2 - 1 || x == MAZE_WIDTH/2) &&
           (y == MAZE_HEIGHT/2 - 1 || y == MAZE_HEIGHT/2);
}