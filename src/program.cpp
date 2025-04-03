#include "program.hpp"

Program::Program()
{
    window = new sf::RenderWindow;
    window->create({1280, 720}, "Space", sf::Style::Titlebar | sf::Style::Close);
    window->setFramerateLimit(60);

    PlayerUI::init(window);
    
    {
        sf::View view;
        view.setViewport(sf::FloatRect{{0.f, 0.f}, {0.5f, 1.f}});
        view.zoom(0.15f);
        p1UI.setView(view);
    }
    {
        sf::View view;
        view.setViewport(sf::FloatRect{{0.5f, 0.f}, {0.5f, 1.f}});
        view.zoom(0.15f);
        p2UI.setView(view);
    }

    PlayerKeyBinds p1Binds{sf::Keyboard::W, sf::Keyboard::S, sf::Keyboard::A, sf::Keyboard::D, sf::Keyboard::T, sf::Keyboard::G, sf::Keyboard::F, sf::Keyboard::H};
    PlayerKeyBinds p2Binds{sf::Keyboard::Up, sf::Keyboard::Down, sf::Keyboard::Left, sf::Keyboard::Right, sf::Keyboard::I, sf::Keyboard::K, sf::Keyboard::J, sf::Keyboard::L};

    p1UI.setPlayerPos({0.f,0.f}).setTextureName("resources/textures/Spaceship_tut.png").setKeyBinds(p1Binds);
    p2UI.setPlayerPos(static_cast<sf::Vector2f>(window->getSize())).setTextureName("resources/textures/Spaceship_tut_thin.png").setKeyBinds(p2Binds);

    p1UI.setSecondPlayer(p2UI);
    p2UI.setSecondPlayer(p1UI);
    
    #if DEVINFO
    p1UI.setStatsPos({window->getSize().x / 2.f - 200.f, 0.f});
    player2.setStatsPos({window->getSize().x - 240.f, 0.f});
    #endif
}

Program::~Program()
{
    delete window;
}

void Program::handleEvents()
{
    sf::Event ev;
    while (window->pollEvent(ev))
    {
        if (ev.type == sf::Event::Closed)
            window->close();
        p1UI.handleEvents(ev);
        p2UI.handleEvents(ev);
    }
}

void Program::update()
{
    p1UI.update();
    p2UI.update();
}

void Program::display()
{
    window->clear();
    
    p1UI.display(window);

    p2UI.display(window);

    window->setView(window->getDefaultView());
    #if DEVINFO
    window->draw(player1.getStats());
    window->draw(player2.getStats());
    #endif

    window->display();
}
