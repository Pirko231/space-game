#pragma once
#include "laserFactory.hpp"
#include "rocketFactory.hpp"
#include "scannerFactory.hpp"

class MissileManager
{
public:
    /// @brief tworzy pocisk i przechowuje go w wektorze
    /// @param factoryType rodzaj fabryki, rozne fabryki wytwarzaja rozne pociski @see missileFactory
    /// @param pos pozycja startowa
    /// @param dir pozycja celownika
    void create(IMissileFactory& factoryType, sf::Vector2f pos, sf::Vector2f dir);

    /// @brief porusza wszystkie pociski ktore przechowuje
    void update();

    const std::vector<std::unique_ptr<Missile>>& getMissiles() const {return missiles;}

private:
    std::vector<std::unique_ptr<Missile>> missiles;
};