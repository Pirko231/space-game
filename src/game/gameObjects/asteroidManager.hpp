#pragma once
#include "asteroidFactory.hpp"

class AsteroidManager
{
public:
    AsteroidManager(int amount);

    void update();

    const std::vector<std::unique_ptr<Asteroid>>& getAsteroids() const {return asteroids;}

    void shouldDelete(int index);

private:
    std::vector<std::unique_ptr<Asteroid>> asteroids;
};