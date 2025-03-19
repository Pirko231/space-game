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
public:
    Program();
    ~Program();
    bool running() const {return window->isOpen();}
    void handleEvents();
    void update();
    void display();
private:
    sf::RenderWindow* window;

    sf::Texture p1BackgroundTxt;
    sf::Sprite p1Background;
    sf::Texture p2BackgroundTxt;
    sf::Sprite p2Background;

    Player player1;
    Player player2;
};