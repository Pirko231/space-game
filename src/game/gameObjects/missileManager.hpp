#pragma once
#include "laserFactory.hpp"
#include "rocketFactory.hpp"
#include "scannerFactory.hpp"

class MissileManager
{
public:
    void create(sf::Vector2f pos, sf::Vector2f dir);
    void update();

    const std::vector<std::unique_ptr<Missile>>& getMissiles() const {return missiles;}

private:
    std::vector<std::unique_ptr<Missile>> missiles;
};