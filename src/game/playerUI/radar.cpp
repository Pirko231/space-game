#include "radar.hpp"

Radar::Radar() : sprite{util::AssetLoader::get().radar}
{
    sprite.setScale({0.16f,0.16f});
}

void Radar::update(const Player* player)
{
    findTargets(player->getCenter());
    removeTargets(player->getCenter());
    moveTargets();
    convertCoordinates();
}

void Radar::findTargets(sf::Vector2f playerPos)
{
    sf::FloatRect hitbox{{playerPos.x - range / 2.f, playerPos.y - range / 2.f}, {range, range}};
    for (auto& i : asteroids->getAsteroids())
    {
        //zeby uniknac powtorzen
        if (!isRepeated(&i) || currentlyDisplayed.empty())
        {
            //pierwsze wrzucenie do radaru (razem z adresem)
            if (hitbox.findIntersection(i->getGlobalBounds()))
            {
                sf::RectangleShape shape{{5.f,5.f}};
                shape.setPosition(i->getGlobalBounds().position);
                currentlyDisplayed.push_back({std::move(shape), &i});
            }
        }
    }
}

void Radar::removeTargets(sf::Vector2f playerPos)
{
    sf::FloatRect hitbox{{playerPos.x - range / 2.f, playerPos.y - range / 2.f}, {range, range}};
    for (std::size_t i = 0; i < currentlyDisplayed.size(); i++)
        if (!hitbox.findIntersection(currentlyDisplayed[i].second->operator->()->getGlobalBounds()))
        {
            currentlyDisplayed.erase(currentlyDisplayed.begin() + i);
            i--;
        }
            
}

void Radar::convertCoordinates()
{
    sf::Vector2f basePos{sprite.getPosition()};

}

bool Radar::isRepeated(const std::unique_ptr<Asteroid>* obj)
{
    if (!currentlyDisplayed.empty())
        for (auto& [shape, adress] : currentlyDisplayed)
            if (obj == adress)
                return true;
    return false;
}

void Radar::moveTargets()
{
    for (auto& [shape, adress] : currentlyDisplayed)
        shape.setPosition(adress->operator->()->getGlobalBounds().position);
}
