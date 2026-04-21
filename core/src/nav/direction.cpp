#include "direction.h"

Direction navigationDirection::rightDirection(Direction heading)
{

    // TODO: Convert in verbose
    std::cout << "Right is " << ((heading + 1) % 4) << std::endl;
    // TODO Blink once
    return static_cast<Direction>((heading + 1) % 4);
}


Direction navigationDirection::leftDirection(Direction heading)
{

    // TODO: Convert in verbose
    std::cout << "Left is " << ((heading + 3) % 4) << std::endl;
    // TODO Blink three times
    return static_cast<Direction>((heading + 3) % 4);
}


Direction navigationDirection::backDirection(Direction heading)
{

    // TODO: Convert in verbose
    std::cout << "The opposite direction is " << ((heading + 2) % 4) << std::endl;
    // TODO Blink once long
    return static_cast<Direction>((heading + 2) % 4);
}