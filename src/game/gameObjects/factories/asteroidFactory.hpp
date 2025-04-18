#pragma once
#include "missiles/asteroid.hpp"
#include <memory>

class AsteroidFactory
{
public:
    std::unique_ptr<Asteroid> create(sf::Vector2f _pos, sf::Vector2f moveBy)
    {
        return std::make_unique<Asteroid>(Asteroid{_pos, moveBy, util::AssetLoader::get().asteroids[0]});
    }
};