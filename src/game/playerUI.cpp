#include "playerUI.hpp"

sf::RenderWindow* PlayerUI::window {nullptr};
sf::Sprite PlayerUI::background{util::AssetLoader::get().background};

PlayerUI::PlayerUI() : player{util::AssetLoader::get().ship1}
{
    player.setView(&view);
}

void PlayerUI::handleEvents(const std::optional<sf::Event>& ev)
{
    player.handleEvents(ev);
}

void PlayerUI::update()
{
    player.update();
}

void PlayerUI::display(sf::RenderWindow *window)
{
    view.setCenter(player.getCenter());
    window->setView(view);
    window->draw(background);
    window->draw(player);
    window->draw(*player2);

    for (auto& i : player.getMissileManager()->getMissiles())
        window->draw(*i);
}

void PlayerUI::init(sf::RenderWindow* _window)
{
    window = _window;
    background.setPosition({-(window->getSize().x * 2.f), -(window->getSize().y * 4.f)});
    background.setScale({4.f,4.f});
}
