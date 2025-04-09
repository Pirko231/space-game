#pragma once
#include <SFML/Graphics.hpp>
#include <memory>
#include "missile.hpp"

class IMissileFactory
{
public:
    virtual std::unique_ptr<Missile> create(sf::Vector2f pos, sf::Vector2f dir) = 0;
    virtual ~IMissileFactory() = default;
};