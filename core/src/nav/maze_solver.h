#pragma once

#include <iostream>
#include "maze.h"
#include "log.h"
#include "navigation.h"

// Polimorphism: ISolver virtual -> append the desired algorithm
extern "C" class ISolver
{ 
    public:
        virtual ~ISolver() = default;        // distruttore virtuale, implementazione default
        virtual Direction nextStep(const mazeGrid& maze, const Position& actual_position) = 0; // metodo puro, nessuna implementazione
    private:
};


extern "C" class RightHandSolver : public ISolver
{ 
    public:
        Direction nextStep(const mazeGrid& maze, const Position& actual_position) override;

    private:
};

extern "C" class FloodFillSolver : public ISolver
{ 
    public:

    private:
};