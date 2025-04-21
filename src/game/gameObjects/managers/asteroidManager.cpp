#include "asteroidManager.hpp"

AsteroidManager::AsteroidManager(int amount, const Map* _map)
{
    AsteroidFactory factory;
    map = _map;
    for (int i = 0; i < amount; i++)
    {
        //jedynka na koncu aby uniknac normalizacji wektora 0,0
        sf::Vector2f startPos{static_cast<float>(std::rand() % static_cast<int>(map->getBounds().size.x)), static_cast<float>(std::rand() % static_cast<int>(map->getBounds().size.y) + 1)};
        

        sf::Vector2f moveBy{startPos.normalized()};
        if (std::rand() % 2)
            moveBy.x *= -1;
        if (std::rand() % 2)
            moveBy.y *= -1.f;

        if (moveBy.x == 0 && moveBy.y == 0)
            moveBy += {0.1,0.1};
        asteroids.push_back(factory.create(startPos, moveBy.normalized()));
    }
}

void AsteroidManager::update()
{
    timer.update();
    //check kolizji z mapa
    if (timer.hasTimePassed())
    {
        for (auto& i : asteroids)
        {
            if (!i->getGlobalBounds().findIntersection(map->getBounds()))
                i->del();
        }
        timer.restart();
    }

    //ruch i kasowanie
    for (std::size_t i = 0; i < asteroids.size(); i++)
    {
        asteroids[i]->update();
        if (asteroids[i]->shouldDelete())
        {
            asteroids.erase(asteroids.begin() + i);
            i--;
        }
    }
}

void AsteroidManager::display(sf::RenderWindow *window)
{
    for (auto& i : asteroids)
        window->draw(*i);
}

void AsteroidManager::shouldDelete(int index)
{
}
