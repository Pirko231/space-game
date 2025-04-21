#pragma once
#include <SFML/Graphics.hpp>
#include "assetLoader.hpp"

class Shield : public sf::Drawable
{
public:
    Shield()
    : sprite{util::AssetLoader::get().shield}
    {
        sprite.setOrigin(sprite.getGlobalBounds().getCenter());
        sprite.setScale({0.1f,0.1f});
    }
    void setPosition(sf::Vector2f pos) {sprite.setPosition(pos);}
    int getDamageResistance() const {return protection;}
    float getEnergyUse() const {return energyUse;}
    bool isActive() const {return active;}
    void activate(bool status) {active = status;}
private:
    sf::Sprite sprite;
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override
    {
        target.draw(sprite, states);
    }
    int protection{10};
    float energyUse{5.f};
    bool active{};
};