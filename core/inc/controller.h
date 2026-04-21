#pragma once

#include <iostream>
#include "navigation.h"

/* The degrees of rotation are clockwise following the compass */

extern "C" class Controller
{ 
    public:
        void init();

    private:
        float calculateRotation(const Direction OldDir, const Direction NewDir);
        bool e_turn(const float degrees);
        bool e_goAhead();
        float sensors();
        bool motor_setup();
};