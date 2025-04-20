#include "hitChecker.hpp"

void HitChecker::check()
{
    for (auto& obj : p1Missiles->getMissiles())
    {
        if (obj->getGlobalBounds().findIntersection(p2Hitbox->getGlobalBounds()))
        {
            obj->del();
            p2Hitbox->damaged(obj->getDamage());
        }
    }
    for (auto& obj : p2Missiles->getMissiles())
    {
        if (obj->getGlobalBounds().findIntersection(p1Hitbox->getGlobalBounds()))
        {
            obj->del();
            p1Hitbox->damaged(obj->getDamage());
        }
    }

    for (auto& aster : asteroids->getAsteroids())
    {
        if (p1Hitbox->getGlobalBounds().findIntersection(aster->getGlobalBounds()))
        {
            p1Hitbox->damaged(aster->getDamage());
            aster->del();
        }
        if (p2Hitbox->getGlobalBounds().findIntersection(aster->getGlobalBounds()))
        {
            p2Hitbox->damaged(aster->getDamage());
            aster->del();
        }
    }
}