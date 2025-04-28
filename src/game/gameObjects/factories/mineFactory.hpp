#pragma once
#include "missileFactory.hpp"
#include "missiles/mine.hpp"

class MineFactory : public IMissileFactory
{
public:
    std::unique_ptr<Missile> create(sf::Vector2f pos, sf::Vector2f moveBy) override
    {
        //wczytanie tekstury
        if (Mine::shouldInit())
            Mine::init();

        
        return std::make_unique<Mine>(Mine{pos, moveBy});
    }

    int cost() const override {return 5;}
    
    ~MineFactory() = default;
};