#include "rocket.hpp"

void Rocket::init()
{
}

void Rocket::handleEvents(const std::optional<sf::Event>& ev)
{
    if (const auto* keyReleased = ev->getIf<sf::Event::KeyPressed>())
    {
        if (keyReleased->code == sf::Keyboard::Key::A)
        {
            sprite.rotate(-rotationSpeed);
            moveBy = moveBy.rotatedBy(-rotationSpeed);
        }
        if (keyReleased->code == sf::Keyboard::Key::D)
        {
            sprite.rotate(rotationSpeed);
            moveBy = moveBy.rotatedBy(rotationSpeed);
        }
    }
}

void Rocket::update()
{
    sprite.move(moveBy);
    lifeSpan++;
}

void Rocket::display()
{
}
