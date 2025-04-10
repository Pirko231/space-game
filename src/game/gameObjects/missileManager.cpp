#include "missileManager.hpp"

void MissileManager::create(IMissileFactory& factoryType, sf::Vector2f pos, sf::Vector2f dir)
{
    missiles.push_back(factoryType.create(pos, dir));
}

void MissileManager::update()
{
}
