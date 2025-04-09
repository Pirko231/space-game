#pragma once
#include "missileFactory.hpp"
#include "missiles/rocket.hpp"


class RocketFactory : public IMissileFactory
{
public:
    std::unique_ptr<Missile> create(sf::Vector2f pos, sf::Vector2f dir) override
    {
        //wczytanie tekstury
        if (Rocket::shouldInit())
            Rocket::init();

        
        return std::make_unique<Rocket>(Rocket{pos, dir});
    }
    ~RocketFactory() = default;
};