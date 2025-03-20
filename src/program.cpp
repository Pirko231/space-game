#include "program.hpp"

Program::Program()
{
    window = new sf::RenderWindow;
    window->create({1280, 720}, "Space", sf::Style::Titlebar | sf::Style::Close);
    window->setFramerateLimit(60);

    p1BackgroundTxt.loadFromFile("resources/textures/gameBackground.png");
    p1Background.setTexture(p1BackgroundTxt);
    p1View.setViewport(sf::FloatRect{{0.f, 0.f}, {0.5f, 1.f}});

    p2BackgroundTxt.loadFromFile("resources/textures/gameBackground.png");
    p2Background.setTexture(p2BackgroundTxt);
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

    //p1View = sf::View{{player1.getPosition().x, player1.getPosition().y}, {window->getSize().x / 2.f, window->getSize().y / 2.f}};
    
    //p1View.setCenter(50.f,50.f);
    //p1View.zoom(2.f);
    p1Background.setPosition(0.f,0.f);
    window->draw(p1Background);
    
    p1View.setCenter(player1.getCenter());
    p1View.zoom(1.f);
    window->setView(p1View);
    window->draw(player1);

    p2View.setCenter(player2.getCenter());
    window->setView(p2View);
    window->draw(p2Background);
    window->draw(player2);

    window->display();
}
