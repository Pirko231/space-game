#pragma once
#include "factories/laserFactory.hpp"
#include "factories/rocketFactory.hpp"
#include "factories/scannerFactory.hpp"
#include "timer.hpp"

class MissileManager
{
public:
    /// @brief tworzy pocisk i przechowuje go w wektorze
    /// @param factoryType rodzaj fabryki, rozne fabryki wytwarzaja rozne pociski @see missileFactory
    /// @param pos pozycja startowa
    /// @param dir pozycja celownika
    /// @return czy udalo sie utworzyc pocisk
    bool create(IMissileFactory& factoryType, sf::Vector2f pos, sf::Vector2f dir);

    void handleEvents(const Pressed& pressed);
    
    /// @brief porusza wszystkie pociski ktore przechowuje
    void update(bool* rocketRecentlyDeleted);

    const std::vector<std::unique_ptr<Missile>>& getMissiles() const {return missiles;}

    const std::optional<Rocket*>& getRocket() const {return rocket;}

private:
    std::vector<std::unique_ptr<Missile>> missiles;
    std::optional<Rocket*> rocket;
    util::Timer rocketTimer{util::secondsToFrames(10)};
};