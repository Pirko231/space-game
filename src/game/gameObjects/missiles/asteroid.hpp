#pragma once
#include <SFML/Graphics.hpp>
#include "assetLoader.hpp"

class Asteroid : public sf::Drawable
{
public:
    Asteroid(sf::Vector2f _pos, sf::Vector2f _moveBy, sf::Texture& _texture)
    : sprite{_texture}
    {
        moveBy = _moveBy / 20.f;
        rotationPerFrame = moveBy.angle() + sf::degrees(static_cast<float>(std::rand() % 45));
        rotationPerFrame /= 50.f;
        sprite.setOrigin(sprite.getGlobalBounds().getCenter());
        sprite.setPosition(_pos);
        sprite.setScale({0.2f,0.2f});
    }
    void update()
    {
        sprite.move(moveBy);
        sprite.rotate(rotationPerFrame);
    }
private:
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override
    {
        target.draw(sprite, states);
    }
    sf::Sprite sprite;
    sf::Vector2f moveBy;
    sf::Angle rotationPerFrame;
};