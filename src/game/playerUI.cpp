#include "playerUI.hpp"

sf::RenderWindow* PlayerUI::window {nullptr};
sf::Sprite PlayerUI::background{util::AssetLoader::get().background};

PlayerUI::PlayerUI()
: player{util::AssetLoader::get().ship1}, healthBar{player.getHealth()}, energyBar{player.getEnergy()}
{
    player.setView(&view);

    healthBar.setColor(sf::Color::Red);
    energyBar.setColor(sf::Color::Blue);
}

void PlayerUI::handleEvents(const std::optional<sf::Event>& ev)
{
    player.handleEvents(ev);
}

void PlayerUI::update()
{
    player.update();

    healthBar.manageHover(sf::Mouse::getPosition());
    energyBar.manageHover(sf::Mouse::getPosition());
    healthBar.move(player.getMoveBy());
    energyBar.move(player.getMoveBy());
}

void PlayerUI::display(sf::RenderWindow *window)
{
    view.setCenter(player.getGlobalBounds().getCenter());
    window->setView(view);
    window->draw(background);
    window->draw(player);
    window->draw(*player2);
    window->draw(healthBar);
    window->draw(energyBar);

    for (auto& i : player.getMissileManager()->getMissiles())
        window->draw(*i);
    for (auto& i : player2->getMissileManager()->getMissiles())
        window->draw(*i);
}

void PlayerUI::init(sf::RenderWindow* _window)
{
    window = _window;
    background.setPosition({-(window->getSize().x * 2.f), -(window->getSize().y * 4.f)});
    background.setScale({4.f,4.f});
}
