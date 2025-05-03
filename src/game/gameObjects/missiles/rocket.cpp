#include "rocket.hpp"

sf::Sound Rocket::sound{util::AssetLoader::get().rocketSound};

void Rocket::handleEvents(const Pressed& _pressed) const
{
    pressed = &_pressed;
}

void Rocket::update()
{
    sprite.move(moveBy);

    if (pressed->a)
    {
        sprite.rotate(-rotationSpeed);
        moveBy = moveBy.rotatedBy(-rotationSpeed);
    }
    if (pressed->d)
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
