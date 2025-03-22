#pragma once

#include <SFML/Graphics.hpp>

#include "game/player.hpp"

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

    sf::Texture backgroundTxt;
    sf::Sprite background;
    //sf::Texture p2BackgroundTxt;
    //sf::Sprite p2Background;

    PlayerKeyBinds p1Binds;
    PlayerKeyBinds p2Binds;

    Player player1;
    Player player2;

private:
    #if DEVINFO
    
    #endif
};