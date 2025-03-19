#include "program.hpp"

Program::Program()
{
    window = new sf::RenderWindow;
    window->create({1280, 720}, "Space", sf::Style::Titlebar | sf::Style::Close);
    window->setFramerateLimit(60);

    p1BackgroundTxt.loadFromFile("resources/textures/gameBackground.png");
    p1Background.setTexture(p1BackgroundTxt);

    p2BackgroundTxt.loadFromFile("resources/textures/gameBackground.png");
    p2Background.setTexture(p2BackgroundTxt);

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

    window->setView(sf::View{player1.getCenter(), {window->getSize().x / 2.f, 0.f}});
    window->draw(player1);

    window->display();
}
