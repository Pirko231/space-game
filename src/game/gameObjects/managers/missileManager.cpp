#include "missileManager.hpp"

void MissileManager::create(IMissileFactory& factoryType, sf::Vector2f pos, sf::Vector2f dir)
{
    missiles.push_back(factoryType.create(pos, dir));
}

void MissileManager::update()
{
    for (std::size_t i = 0; i < missiles.size(); i++)
    {
        missiles[i]->update();
        if (missiles[i]->shouldDelete())
        {
            missiles.erase(missiles.begin() + i);
            i--;
        }
    }
}
