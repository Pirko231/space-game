#pragma once

#include <SFML/Graphics.hpp>
#include "pressed.hpp"

#ifdef MEMTRACKER
#include "../perf/memTracker.hpp"
#endif

class Player : public sf::Drawable
{
public:
    Player(const std::string&);

    void handleEvents(sf::Event);

    void update();

    sf::Vector2f getCenter() const {return {sprite.getPosition().x + sprite.getLocalBounds().width / 2.f, sprite.getPosition().y + sprite.getLocalBounds().height / 2.f};}

    sf::Vector2f getPosition() const {return sprite.getPosition();}
private:
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override
    {
        target.draw(sprite, states);
    }

    Pressed pressed;

    sf::Vector2f moveBy;

    float throttle{5.f};

    sf::Sprite sprite;
    sf::Texture mainTexture;
};