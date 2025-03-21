#include "player.hpp"

Player::Player(const std::string& textureFilename, sf::Keyboard::Key _up, sf::Keyboard::Key _down, sf::Keyboard::Key _left, sf::Keyboard::Key _right)
{
    mainTexture.loadFromFile(textureFilename);
    sprite.setTexture(mainTexture);
    up = _up;
    down = _down;
    left = _left;
    right = _right;
}

void Player::handleEvents(const sf::Event& ev)
{
    if (ev.type == sf::Event::KeyPressed)
    {
        if (ev.key.code == up)
            pressed.w = true;
        if (ev.key.code == down)
            pressed.s = true;
        if (ev.key.code == left)
            pressed.a = true;
        if (ev.key.code == right)
            pressed.d = true;
    }

    if (ev.type == sf::Event::KeyReleased)
    {
        if (ev.key.code == up)
            pressed.w = false;
        if (ev.key.code == down)
            pressed.s = false;
        if (ev.key.code == left)
            pressed.a = false;
        if (ev.key.code == right)
            pressed.d = false;
    }
}

void Player::update()
{
    if (pressed.w && moveBy.y < maxSpeed)
    {
        moveBy.y -= throttle;
    }
    else if (pressed.s && moveBy.y > -(maxSpeed / 4.f))
    {
        moveBy.y += throttle / 2.5f;
    }
    else
    {
        if (moveBy.y > 0)
            moveBy.y -= throttle / 5.f;
        if (moveBy.y < 0)
            moveBy.y += throttle / 5.f;
    }
    sprite.move(moveBy);
}
