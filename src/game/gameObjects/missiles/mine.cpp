#include "mine.hpp"

void Mine::update()
{
    sprite.move(moveBy);
    lifeSpan++;
}

void Mine::display()
{
}
