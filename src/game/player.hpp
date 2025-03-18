#pragma once

#include <SFML/Graphics.hpp>

#ifdef MEMTRACKER
#include "../perf/memTracker.hpp"
#endif

class Player : public sf::Drawable
{
public:
    Player();
private:
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override
    {
        target.draw(sprite, states);
    }

    sf::Sprite sprite;
    sf::Texture mainTexture;
};