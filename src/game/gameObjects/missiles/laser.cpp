#include "laser.hpp"

void Laser::update()
{
    sprite.move(moveBy);
    lifeSpan++;
    //sound.play();
}

void Laser::display()
{
}
