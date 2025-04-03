#pragma once

#include <SFML/Graphics.hpp>

#include "game/playerUI.hpp"

#ifdef MEMTRACKER
#include "perf/memTracker.hpp"
#endif

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

private:
    #if DEVINFO
    
    #endif
};