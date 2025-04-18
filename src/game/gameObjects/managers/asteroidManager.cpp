#include "asteroidManager.hpp"

AsteroidManager::AsteroidManager(int amount)
{
    AsteroidFactory factory;
    for (int i = 0; i < amount; i++)
    {
        
        sf::Vector2f startPos{static_cast<float>(std::rand() % 4000),static_cast<float>(std::rand() % 4000)};
        if (std::rand() % 2)
            startPos.x *= -1;
        if (std::rand() % 2)
            startPos.y *= -1.f;
            
        
        sf::Vector2f moveBy{startPos.normalized()};
        if (moveBy.x == 0 && moveBy.y == 0)
            moveBy += {0.1,0.1};
        asteroids.push_back(factory.create(startPos, moveBy.normalized()));
    }
}

void AsteroidManager::update()
{
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
