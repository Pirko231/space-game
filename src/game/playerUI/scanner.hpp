#pragma once
#include <SFML/Graphics.hpp>

class Scanner
{
public:
    static sf::Color setColor(int temperature)
    {
        if (temperature < 100)
            return sf::Color::White;
        if (temperature < 600)
            return sf::Color::Blue;
        if (temperature < 1200)
            return sf::Color::Yellow;
        if (temperature < 2000)
            return sf::Color{255,128,0};
        return sf::Color::Red;
    }
    void setStatus(bool _status) {status = _status;}
    bool isActive() const {return status;}
    float getRange() const {return range;}
    sf::Vector2f getRectSize() const {return rectSize;}
    float getEnergyUse() const {return energyUse;}
private:
    bool status{};
    float range{util::ConfigLoader::get().scannerRange};
    float energyUse{util::ConfigLoader::get().scannerEnergyUse};
    sf::Vector2f rectSize{1.f,1.f};
};