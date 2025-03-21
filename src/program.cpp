#include "program.hpp"

Program::Program()
{
    window = new sf::RenderWindow;
    window->create({1280, 720}, "Space", sf::Style::Titlebar | sf::Style::Close);
    window->setFramerateLimit(60);

    backgroundTxt.loadFromFile("resources/textures/gameBackground.png");
    background.setTexture(backgroundTxt);
    background.setPosition(-(window->getSize().x / 2.f), -(window->getSize().y / 2.f));
    

    p1View.setViewport(sf::FloatRect{{0.f, 0.f}, {0.5f, 1.f}});
    p2View.setViewport(sf::FloatRect{{0.5f, 0.f}, {0.5f, 1.f}});

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
        player1.handleEvents(ev);
    }
}

void Program::update()
{
    player1.update();
}

void Program::display()
{
    window->clear();
    
    p1View.setCenter(player1.getCenter());
    window->setView(p1View);
    window->draw(background);
    p1View.zoom(1.f);
    window->draw(player1);

    p2View.setCenter(player2.getCenter());
    window->setView(p2View);
    window->draw(background);
    p2View.zoom(1.f);
    window->draw(player2);

    window->display();
}
