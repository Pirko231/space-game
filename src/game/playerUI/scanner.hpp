#pragma once
#include <SFML/Graphics.hpp>

class Scanner
{
public:
    void setStatus(bool _status) {status = _status;}
    bool isActive() const {return status;}
    float getRange() const {return range;}
    sf::Vector2f getRectSize() const {return rectSize;}
    float getEnergyUse() const {return energyUse;}
private:
    bool status{};
    float range{4000.f};
    float energyUse{5};
    sf::Vector2f rectSize{1.f,1.f};
};