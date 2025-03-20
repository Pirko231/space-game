#include "player.hpp"

Player::Player(const std::string& textureFilename)
{
    mainTexture.loadFromFile(textureFilename);
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
    else if (pressed.s)
    {
        moveBy.y -= throttle;
    }
    else
    {
        if (moveBy.y > 0)
            moveBy.y -= throttle / 4.f;
        if (moveBy.y < 0)
            moveBy.y += throttle / 4.f;
    }
    sprite.move(moveBy);
}
