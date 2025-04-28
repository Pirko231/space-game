#pragma once
#include "missileFactory.hpp"
#include "missiles/laser.hpp"

class LaserFactory : public IMissileFactory
{
public:
    std::unique_ptr<Missile> create(sf::Vector2f pos, sf::Vector2f dir) override
    {    
        return std::make_unique<Laser>(Laser{pos, dir});
    }
    
    int cost() const override {return 5;}

    ~LaserFactory() = default;
};