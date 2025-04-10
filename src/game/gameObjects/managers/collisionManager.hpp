#pragma once
#include "missileManager.hpp"
#include "asteroidManager.hpp"

/// @brief przechowuje dane o pozycji pociskow, asteroid i graczy
class CollisionManager
{
public:
    static void setData(const MissileManager* p1Manager, const MissileManager* p2Manager, const sf::Sprite* p1, const sf::Sprite* p2, const AsteroidManager* asteroidManager)
    {
        p1Missiles = p1Manager; p2Missiles = p2Manager;
        p1Hitbox = p1; p2Hitbox = p2;
        asteroids = asteroidManager;
    }
protected:
    static const MissileManager* p1Missiles;
    static const MissileManager* p2Missiles;

    static const sf::Sprite* p1Hitbox;
    static const sf::Sprite* p2Hitbox;

    static const AsteroidManager* asteroids;
};

inline const MissileManager* CollisionManager::p1Missiles{};
inline const MissileManager* CollisionManager::p2Missiles{};

inline const sf::Sprite* CollisionManager::p1Hitbox{};
inline const sf::Sprite* CollisionManager::p2Hitbox{};

inline const AsteroidManager* CollisionManager::asteroids{};