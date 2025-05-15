#include "rocket.hpp"

sf::Sound Rocket::sound{util::AssetLoader::get().rocketSound};

void Rocket::handleEvents(const Pressed& _pressed) const
{
    keys = &_pressed;
}

void Rocket::update()
{
    sprite.move(moveBy);

    if (keys->at(binds.left).pressed)
    {
        sprite.rotate(-rotationSpeed);
        moveBy = moveBy.rotatedBy(-rotationSpeed);
    }
    if (keys->at(binds.right).pressed)
    {
        sprite.rotate(rotationSpeed);
        moveBy = moveBy.rotatedBy(rotationSpeed);
    }

    lifeSpan++;
    if (flySound.getStatus() != sf::Sound::Status::Playing)
        flySound.play();
}

void Rocket::display()
{
}
