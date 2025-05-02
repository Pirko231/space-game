#pragma once
#include <SFML/Graphics.hpp>
#include "assetLoader.hpp"
#include "configLoader.hpp"

class Asteroid : public sf::Drawable
{
public:
    Asteroid(sf::Vector2f _pos, sf::Vector2f _moveBy, sf::Texture& _texture)
    : sprite{_texture}
    {
        moveBy = _moveBy / static_cast<float>(std::rand() % 10 + 10);
        rotationPerFrame = moveBy.angle() + sf::degrees(static_cast<float>(std::rand() % 45));
        rotationPerFrame /= 50.f;
        sprite.setOrigin(sprite.getGlobalBounds().getCenter());
        sprite.setPosition(_pos);
        sf::Vector2f scale{static_cast<float>(std::rand() % 5 + 1), static_cast<float>(std::rand() % 5 + 1)};
        scale /= 10.f;
        sprite.setScale(scale);
    }
    void update()
    {
        sprite.move(moveBy);
        sprite.rotate(rotationPerFrame);
    }

    sf::FloatRect getGlobalBounds() const {return sprite.getGlobalBounds();}

    int getDamage() const {return damage;}

    void del() {health = 0;}

    int getTemperature() const {return temperature;}

    bool shouldDelete() const {return health <= 0;}
private:
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override
    {
        target.draw(sprite, states);
    }
    sf::Sprite sprite;
    sf::Vector2f moveBy;
    sf::Angle rotationPerFrame;

    float health{100};
    int damage{util::ConfigLoader::get().asteroidDamage};
    int temperature{};
};