#include "rocket.hpp"

void Rocket::init()
{
}

void Rocket::update()
{
    sprite.move(moveBy);
    lifeSpan++;
}

void Rocket::display()
{
}
