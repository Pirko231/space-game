#include "asteroidManager.hpp"

AsteroidManager::AsteroidManager(int amount)
{
    AsteroidFactory factory;
    for (int i = 0; i < amount; i++)
    {
        //asteroids.push_back(factory.create({0.f,0.f}));
        asteroids.push_back(factory.create({static_cast<float>(std::rand() % 4000),static_cast<float>(std::rand() % 4000)}));
    }
}

void AsteroidManager::update()
{
    for (auto& i : asteroids)
        i->update();
}

void AsteroidManager::display(sf::RenderWindow *window)
{
    for (auto& i : asteroids)
        window->draw(*i);
}

void AsteroidManager::shouldDelete(int index)
{
}
