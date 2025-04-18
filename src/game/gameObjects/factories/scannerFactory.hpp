#pragma once
#include "missileFactory.hpp"
#include "missiles/scanner.hpp"

class ScannerFactory : public IMissileFactory
{
public:
    std::unique_ptr<Missile> create(sf::Vector2f pos, sf::Vector2f moveBy) override
    {
        //wczytanie tekstury
        if (Scanner::shouldInit())
            Scanner::init();

        
        return std::make_unique<Scanner>(Scanner{pos, moveBy});
    }

    int cost() const override {return 5;}
    
    ~ScannerFactory() = default;
};