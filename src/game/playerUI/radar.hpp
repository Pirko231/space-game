#pragma once
#include "managers/collisionManager.hpp"
#include "assetLoader.hpp"

class Radar : private CollisionManager, public sf::Drawable
{
public:
    Radar();

    void setPosition(sf::Vector2f pos) {sprite.setPosition(pos);}

    void update();

    void move(sf::Vector2f offset) {sprite.move(offset);}

    sf::FloatRect getGlobalBounds() const {return sprite.getGlobalBounds();}
private:
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override
    {
        target.draw(sprite, states);
    }
    sf::Sprite sprite;
};