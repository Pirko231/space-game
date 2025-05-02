#include "program.hpp"

Program::Program()
{
    window = new sf::RenderWindow;
    window->create(sf::VideoMode{{1280, 720}, 32}, sf::String{"Space"}, sf::Style::Titlebar | sf::Style::Close | sf::Style::Resize);
    window->setFramerateLimit(60);

    CollisionManager::setData(p1UI.getPlayer().getMissileManager(), p2UI.getPlayer().getMissileManager(), &p1UI.getPlayer(), &p2UI.getPlayer(), &asteroidManager);
    {
        sf::View view;
        view.setViewport(sf::FloatRect{{0.f, 0.f}, {0.5f, 1.f}});
        view.zoom(util::ConfigLoader::get().playerViewZoom);
        p1UI.setView(view);
    }
    {
        sf::View view;
        view.setViewport(sf::FloatRect{{0.5f, 0.f}, {0.5f, 1.f}});
        view.zoom(util::ConfigLoader::get().playerViewZoom);
        p2UI.setView(view);
    }

    PlayerKeyBinds p1Binds{sf::Keyboard::Key::W, sf::Keyboard::Key::S, sf::Keyboard::Key::A, sf::Keyboard::Key::D, sf::Keyboard::Key::F, sf::Keyboard::Key::H, sf::Keyboard::Key::Space, sf::Keyboard::Key::LShift, sf::Keyboard::Key::C, sf::Keyboard::Key::Z, sf::Keyboard::Key::X};
    PlayerKeyBinds p2Binds{sf::Keyboard::Key::Up, sf::Keyboard::Key::Down, sf::Keyboard::Key::Left, sf::Keyboard::Key::Right, sf::Keyboard::Key::J, sf::Keyboard::Key::L, sf::Keyboard::Key::Enter, sf::Keyboard::Key::RShift, sf::Keyboard::Key::RControl, sf::Keyboard::Key::Comma, sf::Keyboard::Key::Period};

    p1UI.setPlayerPos(map.getRandomPoint()).setKeyBinds(p1Binds).setMap(&map).setTexture(util::AssetLoader::get().ship1);
    p2UI.setPlayerPos(map.getRandomPoint()).setKeyBinds(p2Binds).setMap(&map).setTexture(util::AssetLoader::get().ship2);

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

    asteroidManager.display(window);

    p2UI.display(window);

    asteroidManager.display(window); //podwojnie aby bylo na obu widokach

    window->setView(window->getDefaultView());
#if DEVINFO
    window->draw(p1UI.getPlayer().getStats());
    window->draw(p2UI.getPlayer().getStats());
#endif

    window->display();
}
