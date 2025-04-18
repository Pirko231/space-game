#pragma once
#include "factories/asteroidFactory.hpp"

class AsteroidManager
{
public:
    AsteroidManager(int amount);

    /// @brief porusza wszystkie asteroidy ktore przechowuje
    void update();

    /// @brief rysuje asteroidy na ekran
    void display(sf::RenderWindow* window);

    const std::vector<std::unique_ptr<Asteroid>>& getAsteroids() const {return asteroids;}

    
    /// @brief oznacza ktora asteroide nalezy usunac
    /// @param index numer w wektorze asteroidy do usuniecia
    void shouldDelete(int index);

private:
    std::vector<std::unique_ptr<Asteroid>> asteroids;
};