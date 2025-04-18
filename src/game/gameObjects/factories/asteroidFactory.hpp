#pragma once
#include "missiles/asteroid.hpp"
#include <memory>

class AsteroidFactory
{
public:
    std::unique_ptr<Asteroid> create(sf::Vector2f _pos)
    {
        sf::Vector2f moveBy{static_cast<float>(std::rand() % 20), static_cast<float>(std::rand() % 20)};
        if (moveBy.x == 0 && moveBy.y == 0)
            moveBy += {0.1,0.1};
        return std::make_unique<Asteroid>(Asteroid{_pos, moveBy.normalized(), util::AssetLoader::get().asteroids[0]});
    }
};