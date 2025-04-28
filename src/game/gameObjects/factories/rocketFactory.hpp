#pragma once
#include "missileFactory.hpp"
#include "missiles/rocket.hpp"


class RocketFactory : public IMissileFactory
{
public:
    std::unique_ptr<Missile> create(sf::Vector2f pos, sf::Vector2f moveBy) override
    {   
        return std::make_unique<Rocket>(Rocket{pos, moveBy});
    }

    int cost() const override {return 5;}
    
    ~RocketFactory() = default;
};