#include "mine.hpp"

sf::Sound Mine::sound{util::AssetLoader::get().mineSound};

void Mine::update()
{
    sprite.move(moveBy);
    lifeSpan++;
}

void Mine::display()
{
}
