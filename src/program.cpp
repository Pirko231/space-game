#include "program.hpp"

Program::Program()
{
    window = new sf::RenderWindow;
    window->create({1280, 720}, "Space", sf::Style::Titlebar | sf::Style::Close);

    //cala alokacja dodana tutaj
    #if MEMTRACKER

    perf::MemTracker::get().addAlloc(sizeof(*window));

    #endif
}

Program::~Program()
{
    delete window;

    //dealokacja pamieci
    #if MEMTRACKER
    perf::MemTracker::get().addFree(sizeof(*window));
    #endif
}

void Program::handleEvents()
{
    sf::Event ev;
    while (window->pollEvent(ev))
    {
        if (ev.type == sf::Event::Closed)
            window->close();
    }
}

void Program::update()
{
}

void Program::display()
{
    window->clear();

    window->draw(player1);

    window->display();
}
