#pragma once

#include <SFML/Graphics.hpp>

#ifdef MEMTRACKER
#include "perf/memTracker.hpp"
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
};