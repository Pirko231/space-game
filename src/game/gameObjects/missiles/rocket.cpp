#include "rocket.hpp"

void Rocket::init()
{
}

void Rocket::handleEvents(const std::optional<sf::Event>& ev)
{
    if (const auto* keyPressed = ev->getIf<sf::Event::KeyPressed>())
    {
        if (keyPressed->code == sf::Keyboard::Key::A)
        {
            pressed.a = true;
        }
        if (keyPressed->code == sf::Keyboard::Key::D)
        {
            pressed.d = true;
        }
    }
    if (const auto* keyReleased = ev->getIf<sf::Event::KeyReleased>())
    {
        if (keyReleased->code == sf::Keyboard::Key::A)
        {
            pressed.a = false;
        }
        if (keyReleased->code == sf::Keyboard::Key::D)
        {
            pressed.d = false;
        }
    }
    
    
    
    
}

void Rocket::update()
{
    sprite.move(moveBy);

    if (pressed.a)
    {
        sprite.rotate(-rotationSpeed);
        moveBy = moveBy.rotatedBy(-rotationSpeed);
    }
    if (pressed.d)
    {
        sprite.rotate(rotationSpeed);
        moveBy = moveBy.rotatedBy(rotationSpeed);
    }
    
    lifeSpan++;
}

void Rocket::display()
{
}
