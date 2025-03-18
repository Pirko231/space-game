#pragma once

#include <SFML/Graphics.hpp>

#include "game/player.hpp"

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

    Player player1;
    Player player2;
};