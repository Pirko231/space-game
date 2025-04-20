#include "radar.hpp"

Radar::Radar() : sprite{util::AssetLoader::get().radar}
{
    sprite.setScale({0.16f,0.16f});
}

void Radar::update()
{
    findTargets(p1Hitbox->getCenter());
    removeTargets(p1Hitbox->getCenter());
}

void Radar::findTargets(sf::Vector2f playerPos)
{
    sf::FloatRect hitbox{{playerPos.x - range / 2.f, playerPos.y - range / 2.f}, {range, range}};
    for (auto& i : asteroids->getAsteroids())
        if (hitbox.findIntersection(i->getGlobalBounds()))
        {
            sf::RectangleShape shape{{5.f,5.f}};
            shape.setPosition(i->getGlobalBounds().position);
            currentlyDisplayed.push_back({std::move(shape), i->getGlobalBounds().position});
        }
}

void Radar::removeTargets(sf::Vector2f playerPos)
{
    sf::FloatRect hitbox{{playerPos.x - range / 2.f, playerPos.y - range / 2.f}, {range, range}};
    /*for (auto& [shape, pos] : currentlyDisplayed)
        if (!hitbox.contains(pos))*/
    for (std::size_t i = 0; i < currentlyDisplayed.size(); i++)
        if (!hitbox.contains(currentlyDisplayed[i].second))
        {
            currentlyDisplayed.erase(currentlyDisplayed.begin() + i);
            i--;
        }
            
}
