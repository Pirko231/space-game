#pragma once
#include <SFML/Graphics.hpp>

class Asteroid : public sf::Drawable
{
public:
    Asteroid(sf::Vector2f _pos) {sprite.setPosition(_pos);}
private:
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override
    {
        target.draw(sprite, states);
    }
    sf::Sprite sprite;

    static sf::Texture textures[3]; //TODO zaimplementowac size i tesktury
};