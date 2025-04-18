#include "missileManager.hpp"

bool MissileManager::create(IMissileFactory& factoryType, sf::Vector2f pos, sf::Vector2f dir)
{
    //UWAGA, do funkcji nadal wysylane jest dir a nie moveBy
    sf::Vector2f _moveBy{dir.x - pos.x, dir.y - pos.y};   
    if (_moveBy.x == 0.f && _moveBy.y == 0.f)
        return false;
    
    missiles.push_back(factoryType.create(pos, dir));
    return true;
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
