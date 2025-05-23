#pragma once
#include <deque>
#include "factories/laserFactory.hpp"
#include "factories/rocketFactory.hpp"
#include "factories/mineFactory.hpp"
#include "timer.hpp"
#include "explosion.hpp"

class MissileManager
{
public:
    MissileManager(PlayerKeyBinds& _binds) : binds{_binds}
    {
        rocketTimerText.setFillColor(sf::Color::Red);
        explosionSound.setVolume(util::ConfigLoader::get().soundVolume * 0.5f);
    }
    /// @brief tworzy pocisk i przechowuje go w wektorze
    /// @param factoryType rodzaj fabryki, rozne fabryki wytwarzaja rozne pociski @see missileFactory
    /// @param pos pozycja startowa
    /// @param dir pozycja celownika
    /// @return czy udalo sie utworzyc pocisk
    bool create(IMissileFactory& factoryType, sf::Vector2f pos, sf::Vector2f dir);

    void handleEvents(const Pressed& pressed) const;
    
    /// @brief porusza wszystkie pociski ktore przechowuje
    void update(bool* rocketRecentlyDeleted);

    const std::vector<std::unique_ptr<Missile>>& getMissiles() const {return missiles;}

    const std::optional<Rocket*>& getRocket() const {return rocket;}

    const sf::Text& getRocketTimer() const {return rocketTimerText;}

    const std::deque<Explosion>& getExplosions() const {return explosions;}

    int getRocketCooldown() const {return  rocketTimer.maxValue() - rocketTimer.currentValue();}
    int getMineCooldown() const {return mineTimer.maxValue() - mineTimer.currentValue();}
private:
    mutable std::vector<std::unique_ptr<Missile>> missiles;
    std::optional<Rocket*> rocket;
    util::Timer rocketTimer{util::secondsToFrames(util::ConfigLoader::get().rocketCooldown)};
    sf::Text rocketTimerText{util::AssetLoader::get().font};
    util::Timer mineTimer{util::secondsToFrames(util::ConfigLoader::get().mineCooldown)};

    std::deque<Explosion> explosions;

    static sf::Sound explosionSound;

    PlayerKeyBinds& binds;
};