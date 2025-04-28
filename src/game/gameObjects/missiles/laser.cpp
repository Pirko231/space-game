#include "laser.hpp"

void Laser::update()
{
    sprite.move(moveBy);
    lifeSpan++;
}

void Laser::display()
{
}
