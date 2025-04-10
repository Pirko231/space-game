#pragma once

#include <SFML/Graphics.hpp>

#include "game/playerUI.hpp"
#include "game/gameObjects/hitChecker.hpp"
#include "game/gameObjects/managers/asteroidManager.hpp"

#ifdef SPEEDTRACKER
#include "perf/speedTracker.hpp"
#endif

class Program
{
    //testy jednostkowe
    friend class Tests;
public:
    Program();
    ~Program();
    bool running() const {return window->isOpen();}
    void handleEvents();
    void update();
    void display();
private:
    sf::RenderWindow* window;

    PlayerUI p1UI;

    PlayerUI p2UI;

    AsteroidManager asteroidManager{20};

    CollisionManager collisionManager;
private:
    #if DEVINFO
    
    #endif
};