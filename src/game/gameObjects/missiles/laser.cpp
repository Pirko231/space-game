#include "laser.hpp"

sf::Sound Laser::sound{util::AssetLoader::get().laserSound};

void Laser::update()
{
    sprite.move(moveBy);
    lifeSpan++;
    //sound.play();
}

void Laser::display()
{
}
