#include "program.hpp"

Program::Program()
{
    window = new sf::RenderWindow;
    //window->create();
    window->create(sf::VideoMode{{1280, 720}, 32}, sf::String{"Space"}, sf::Style::Titlebar | sf::Style::Close);
    window->setFramerateLimit(60);

    PlayerUI::init(window);

    CollisionManager::setData(p1UI.getPlayer().getMissileManager(), p2UI.getPlayer().getMissileManager(), &p1UI.getPlayer(), &p2UI.getPlayer(), &asteroidManager);
    
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

    PlayerKeyBinds p1Binds{sf::Keyboard::Key::W, sf::Keyboard::Key::S, sf::Keyboard::Key::A, sf::Keyboard::Key::D, sf::Keyboard::Key::T, sf::Keyboard::Key::G, sf::Keyboard::Key::F, sf::Keyboard::Key::H, sf::Keyboard::Key::Space};
    PlayerKeyBinds p2Binds{sf::Keyboard::Key::Up, sf::Keyboard::Key::Down, sf::Keyboard::Key::Left, sf::Keyboard::Key::Right, sf::Keyboard::Key::I, sf::Keyboard::Key::K, sf::Keyboard::Key::J, sf::Keyboard::Key::L, sf::Keyboard::Key::Enter};

    p1UI.setPlayerPos({0.f,0.f}).setTexture(util::AssetLoader::get().ship1).setKeyBinds(p1Binds);
    p2UI.setPlayerPos(static_cast<sf::Vector2f>(window->getSize())).setTexture(util::AssetLoader::get().ship2).setKeyBinds(p2Binds);

    p1UI.setSecondPlayer(p2UI);
    p2UI.setSecondPlayer(p1UI);
    
#if DEVINFO
    p1UI.getPlayer().setStatsPos({window->getSize().x / 2.f - 200.f, 0.f});
    p2UI.getPlayer().setStatsPos({window->getSize().x - 240.f, 0.f});
#endif
}

Program::~Program()
{
    delete window;
}

void Program::handleEvents()
{
    while (const std::optional ev = window->pollEvent())
    {
        if (ev->is<sf::Event::Closed>())
            window->close();
        p1UI.handleEvents(ev);
        p2UI.handleEvents(ev);
    }
}

void Program::update()
{
    p1UI.update();
    p2UI.update();

    asteroidManager.update();

    HitChecker::check();
}

void Program::display()
{
    window->clear();
    
    p1UI.display(window);

    p2UI.display(window);

    asteroidManager.display(window);

    window->setView(window->getDefaultView());
#if DEVINFO
    window->draw(p1UI.getPlayer().getStats());
    window->draw(p2UI.getPlayer().getStats());
#endif

    window->display();
}
