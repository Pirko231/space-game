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

    sf::Texture p1BackgroundTxt;
    sf::Sprite p1Background;
    sf::Texture p2BackgroundTxt;
    sf::Sprite p2Background;

    Player player1{"resources/textures/Spaceship_tut.png", sf::Keyboard::W, sf::Keyboard::S, sf::Keyboard::A, sf::Keyboard::D};
    sf::View p1View;
    Player player2{"resources/textures/Spaceship_tut_thin.png", sf::Keyboard::Up, sf::Keyboard::Down, sf::Keyboard::Left, sf::Keyboard::Right};
    sf::View p2View;

private:
    #if DEVINFO
    
    #endif
};