#include "program.hpp"

Program::Program()
{
    window = new sf::RenderWindow;
    window->create({1280, 720}, "Space", sf::Style::Titlebar | sf::Style::Close);
    window->setFramerateLimit(60);

    backgroundTxt.loadFromFile("resources/textures/gameBackground.png");
    background.setTexture(backgroundTxt);
    background.setPosition(-(window->getSize().x * 2.f), -(window->getSize().y * 4.f));
    background.setScale(4.f,4.f);
    

    p1View.setViewport(sf::FloatRect{{0.f, 0.f}, {0.5f, 1.f}});
    p1View.zoom(0.15f);
    p2View.setViewport(sf::FloatRect{{0.5f, 0.f}, {0.5f, 1.f}});
    p2View.zoom(0.15f);

    UIView.setSize(static_cast<sf::Vector2f>(window->getSize()));
    UIView.setViewport({{0.f, 0.f}, {1.f, 1.f}});

    player1.setPosition({0.f,0.f});
    player2.setPosition(static_cast<sf::Vector2f>(window->getSize()));

    #if DEVINFO
    player1.setStatsPos({window->getSize().x / 2.f - 200.f, 0.f});
    player2.setStatsPos({window->getSize().x - 240.f, 0.f});
    #endif

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
        player2.handleEvents(ev);
    }
}

void Program::update()
{
    player1.update();
    player2.update();
}

void Program::display()
{
    window->clear();
    
    p1View.setCenter(player1.getCenter());
    window->setView(p1View);
    window->draw(background);
    window->draw(player2);
    window->draw(player1);

    p2View.setCenter(player2.getCenter());
    window->setView(p2View);
    window->draw(background);
    window->draw(player1);
    window->draw(player2);

    window->setView(window->getDefaultView());
    #if DEVINFO
    window->draw(player1.getStats());
    window->draw(player2.getStats());
    #endif

    window->display();
}
