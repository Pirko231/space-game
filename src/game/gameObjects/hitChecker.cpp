#include "hitChecker.hpp"

sf::Sound HitChecker::laserSound{util::AssetLoader::get().hitSound};
sf::Sound HitChecker::explosionSound{util::AssetLoader::get().rocketHitSound};

void HitChecker::check()
{
    for (auto& obj : p1Missiles->getMissiles())
    {
        if (obj->getGlobalBounds().findIntersection(p2Hitbox->getGlobalBounds()))
        {
            obj->del();
            p2Hitbox->damaged(obj->getDamage());
            if (dynamic_cast<Laser*>(obj.get()))
                laserSound.play();
            else
                explosionSound.play();
        }
    }
    for (auto& obj : p2Missiles->getMissiles())
    {
        if (obj->getGlobalBounds().findIntersection(p1Hitbox->getGlobalBounds()))
        {
            obj->del();
            p1Hitbox->damaged(obj->getDamage());
            if (dynamic_cast<Laser*>(obj.get()))
                laserSound.play();
            else
                explosionSound.play();
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
        for (auto& obj : p1Missiles->getMissiles())
            if (obj->getGlobalBounds().findIntersection(aster->getGlobalBounds()))
            {
                obj->del();
                aster->dealDamage(obj->getDamage());
            }
        for (auto& obj : p2Missiles->getMissiles())
            if (obj->getGlobalBounds().findIntersection(aster->getGlobalBounds()))
            {
                obj->del();
                aster->dealDamage(obj->getDamage());
            }
    }
}