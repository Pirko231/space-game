#pragma once
#include "missileManager.hpp"
#include "asteroidManager.hpp"

class CollisionManager
{
public:
    static void setData(MissileManager* p1Manager, MissileManager* p2Manager, sf::Sprite* p1, sf::Sprite* p2, AsteroidManager* asteroidManager)
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

const MissileManager* CollisionManager::p1Missiles{};
const MissileManager* CollisionManager::p2Missiles{};

const sf::Sprite* CollisionManager::p1Hitbox{};
const sf::Sprite* CollisionManager::p2Hitbox{};

const AsteroidManager* CollisionManager::asteroids{};