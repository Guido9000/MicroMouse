#include <bitset>

#include "config.h"
#include "maze.h"
#include "log.h"
#include "navigation.h"

using namespace std;

// uint8_t getFlood(uint8_t x, uint8_t y);
// void setFlood(uint8_t x, uint8_t y, uint8_t value);

uint8_t mazeGrid::index(uint8_t x, uint8_t y) const
{
    // TODO: Convert in verbose
    std::cout << "Cell coordinates (" << int(x) << "," << int(y) << ") -> ";
    std::cout << "cell index: " << x * MAZE_WIDTH + y << std::endl;

    return y * MAZE_WIDTH + x;
}


bool mazeGrid::hasWall(uint8_t x, uint8_t y, Direction dir) const
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


void mazeGrid::setWall(uint8_t x, uint8_t y, Direction dir)
{
    setWallCell(x, y, dir);
    setNeighbor(x, y, dir);
}


void mazeGrid::setWallCell(uint8_t x, uint8_t y, Direction dir)
{
    maze_cell& tmp_cell = cells_[index(x,y)];

    tmp_cell.walls |= (1 << dir);

    cout << "Walls in the cell: " << bitset<8>(tmp_cell.walls) << endl;
    LOG_VERBOSE("Maze", "The wall is set");
}


bool mazeGrid::setNeighbor(uint8_t x, uint8_t y, Direction dir)
{
    // No adiacent cell in such direction
    if(isBoarder(x, y, dir))    {return false;}

    // TODO Check axis
    //Move to adiacent cell
    if(dir == NORTH)     {y += 1;}
    else if(dir == SOUTH){y -= 1;}
    else if(dir == EAST) {x += 1;}
    else if(dir == WEST) {x -= 1;}

    setWallCell(x, y, backDirection(dir));

    LOG_VERBOSE("Maze", "The wall in the neighbor cell is set");
    return true;
}

bool mazeGrid::isVisited(uint8_t x, uint8_t y) const
{
    const maze_cell& tmp_cell = cells_[index(x,y)];

    if(tmp_cell.walls & VISITED){
        LOG_VERBOSE("Maze", "The cell was already visited");
        return true;
    }

    LOG_VERBOSE("Maze", "The cell is not visited already");
    return false;
}


void mazeGrid::setVisited(uint8_t x, uint8_t y)
{
    maze_cell& tmp_cell = cells_[index(x,y)];

    tmp_cell.walls |= VISITED;
    LOG_VERBOSE("Maze", "The cell is now visited");

}


void mazeGrid::printCellState(uint8_t x, uint8_t y)
{
    maze_cell tmp_cell = cells_[index(x,y)];

    cout << "Walls in the cell: " << bitset<8>(tmp_cell.walls) << endl;
    cout << "Floods of the cell: " << bitset<8>(tmp_cell.floods) << endl;
}


// Define goal at the center of the maze
bool mazeGrid::isGoal(uint8_t x, uint8_t y) const {
    return (x == MAZE_WIDTH/2 - 1 || x == MAZE_WIDTH/2) &&
           (y == MAZE_HEIGHT/2 - 1 || y == MAZE_HEIGHT/2);
}


bool mazeGrid::isBoarder(uint8_t x, uint8_t y, Direction dir) const
{
    if      (dir == NORTH && y == MAZE_HEIGHT - 1)  {return true;}
    else if (dir == SOUTH && y == 0)                {return true;}
    else if (dir == EAST && y == MAZE_WIDTH - 1)    {return true;}
    else if (dir == WEST && y == 0)                 {return true;}

    else {return false;}
}