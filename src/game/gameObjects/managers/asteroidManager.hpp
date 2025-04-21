#pragma once
#include "factories/asteroidFactory.hpp"
#include "map.hpp"
#include "timer.hpp"

/// @brief przechowuje asteroidy i sprawdza ich kolizje z mapa
class AsteroidManager
{
public:
    AsteroidManager(int amount, const Map*);

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

    const Map* map;

    util::Timer timer{3600};
};