#include "program.hpp"

Program::Program() :
    p1Binds{sf::Keyboard::W, sf::Keyboard::S, sf::Keyboard::A, sf::Keyboard::D, sf::Keyboard::T, sf::Keyboard::G, sf::Keyboard::F, sf::Keyboard::H},
    p2Binds{sf::Keyboard::Up, sf::Keyboard::Down, sf::Keyboard::Left, sf::Keyboard::Right, sf::Keyboard::I, sf::Keyboard::K, sf::Keyboard::J, sf::Keyboard::L}, 
    player1{"resources/textures/Spaceship_tut.png", p1Binds}, player2{"resources/textures/Spaceship_tut_thin.png", p2Binds}
{
    window = new sf::RenderWindow;
    window->create({1280, 720}, "Space", sf::Style::Titlebar | sf::Style::Close);
    window->setFramerateLimit(60);

    backgroundTxt.loadFromFile("resources/textures/gameBackground.png");
    background.setTexture(backgroundTxt);
    background.setPosition(-(window->getSize().x * 2.f), -(window->getSize().y * 4.f));
    background.setScale(4.f,4.f);
    

    player1.getView().setViewport(sf::FloatRect{{0.f, 0.f}, {0.5f, 1.f}});
    player1.getView().zoom(0.15f);
    player2.getView().setViewport(sf::FloatRect{{0.5f, 0.f}, {0.5f, 1.f}});
    player2.getView().zoom(0.15f);


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
    
    player1.getView().setCenter(player1.getCenter());
    window->setView(player1.getView());
    window->draw(background);
    window->draw(player2);
    window->draw(player1);

    player2.getView().setCenter(player2.getCenter());
    window->setView(player2.getView());
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
