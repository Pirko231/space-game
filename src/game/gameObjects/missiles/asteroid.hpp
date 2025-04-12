#pragma once
#include <SFML/Graphics.hpp>
#include "assetLoader.hpp"

class Asteroid : public sf::Drawable
{
public:
    Asteroid(sf::Vector2f _pos) : sprite{util::AssetLoader::get().asteroids[0]} {sprite.setPosition(_pos);}
private:
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override
    {
        target.draw(sprite, states);
    }
    sf::Sprite sprite;
};