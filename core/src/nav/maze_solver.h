#pragma once

#include <iostream>
#include "maze.h"
#include "log.h"
#include "navigation.h"
#include "direction.h"

struct Position;
class mazeGrid;
class Sensor; 

// Polimorphism: ISolver virtual -> append the desired algorithm
class ISolver
{ 
    public:
        virtual ~ISolver() = default;        // distruttore virtuale, implementazione default
        virtual Direction nextStep(const mazeGrid& maze, const Position& actual_position) = 0; // metodo puro, nessuna implementazione
    private:
};


class RightHandSolver : public ISolver
{ 
    public:
        Direction nextStep(const mazeGrid& maze, const Position& actual_position) override;

    private:
};

class FloodFillSolver : public ISolver
{ 
    public:

    private:
};