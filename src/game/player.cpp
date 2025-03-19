#include "player.hpp"

Player::Player()
{
    mainTexture.loadFromFile("resources/textures/Spaceship_tut.png");
    sprite.setTexture(mainTexture);
}

void Player::handleEvents(sf::Event ev)
{
    if (ev.type == sf::Event::KeyPressed)
    {
        if (ev.key.code == sf::Keyboard::W)
            pressed.w = true;
        if (ev.key.code == sf::Keyboard::A)
            pressed.a = true;
        if (ev.key.code == sf::Keyboard::S)
            pressed.s = true;
        if (ev.key.code == sf::Keyboard::D)
            pressed.d = true;
    }

    if (ev.type == sf::Event::KeyReleased)
    {
        if (ev.key.code == sf::Keyboard::W)
            pressed.w = false;
        if (ev.key.code == sf::Keyboard::A)
            pressed.a = false;
        if (ev.key.code == sf::Keyboard::S)
            pressed.s = false;
        if (ev.key.code == sf::Keyboard::D)
            pressed.d = false;
    }
}

void Player::update()
{
    if (pressed.w)
    {
        moveBy.y += throttle;
    }
    if (pressed.w)
    {
        moveBy.y -= throttle;
    }
}
