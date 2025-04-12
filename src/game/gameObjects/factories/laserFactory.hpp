#pragma once
#include "missileFactory.hpp"
#include "missiles/laser.hpp"

class LaserFactory : public IMissileFactory
{
public:
    std::unique_ptr<Missile> create(sf::Vector2f pos, sf::Vector2f moveBy) override
    {
        //wczytanie tekstury
        if (Laser::shouldInit())
            Laser::init();

        
        return std::make_unique<Laser>(Laser{pos, moveBy});
    }
    ~LaserFactory() = default;
};