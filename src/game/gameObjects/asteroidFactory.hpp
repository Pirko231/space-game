#pragma once
#include "asteroid.hpp"
#include <memory>

class AsteroidFactory
{
public:
    std::unique_ptr<Asteroid> create(sf::Vector2f _pos) {return std::make_unique<Asteroid>(Asteroid{_pos});}
};