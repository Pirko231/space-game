#pragma once
#include "missileManager.hpp"
#include "asteroidManager.hpp"
#include "player.hpp"

/// @brief przechowuje dane o pozycji pociskow, asteroid i graczy
class CollisionManager
{
public:
    static void setData(const MissileManager* p1Manager, const MissileManager* p2Manager, const Player* p1, const Player* p2, const AsteroidManager* asteroidManager)
    {
        p1Missiles = p1Manager; p2Missiles = p2Manager;
        p1Hitbox = p1; p2Hitbox = p2;
        asteroids = asteroidManager;
    }
protected:
    static const MissileManager* p1Missiles;
    static const MissileManager* p2Missiles;

    static const Player* p1Hitbox;
    static const Player* p2Hitbox;

    static const AsteroidManager* asteroids;
};

inline const MissileManager* CollisionManager::p1Missiles{};
inline const MissileManager* CollisionManager::p2Missiles{};

inline const Player* CollisionManager::p1Hitbox{};
inline const Player* CollisionManager::p2Hitbox{};

inline const AsteroidManager* CollisionManager::asteroids{};