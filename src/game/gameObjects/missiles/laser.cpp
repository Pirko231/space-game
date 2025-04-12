#include "laser.hpp"

void Laser::init()
{
    
}

void Laser::update()
{
    sprite.move(moveBy);
    lifeSpan++;
}

void Laser::display()
{
}
