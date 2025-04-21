#include "playerUI.hpp"

sf::RenderWindow* PlayerUI::window {nullptr};

PlayerUI::PlayerUI()
: player{util::AssetLoader::get().ship1, pressed, shield}, healthBar{player.getHealth()}, energyBar{player.getEnergy()},
  crosshairPlayer{util::AssetLoader::get().pCrosshair}, crosshairShip{util::AssetLoader::get().sCrosshair}
{
    player.setView(&view);

    healthBar.setColor(sf::Color::Red);
    energyBar.setColor(sf::Color::Blue);

    crosshairPlayer.setScale({0.04f,0.04f});
    crosshairShip.setScale({0.04f,0.04f});
}

void PlayerUI::handleEvents(const std::optional<sf::Event>& ev)
{
    player.handleEvents(ev);

    crosshairHandleEvents(ev);

    if (const auto* keyPressed = ev->getIf<sf::Event::KeyPressed>())
    {
        if (keyPressed->code == keyBinds.shield)
            pressed.shield = true;
        
    }
    
    if (const auto* keyReleased = ev->getIf<sf::Event::KeyReleased>())
    {
        if (keyReleased->code == keyBinds.shoot)
            player.shoot(LaserFactory{}.get(), crosshairShip.getPosition());

        if (keyReleased->code == keyBinds.shield)
            pressed.shield = false;
    }

}

void PlayerUI::update()
{
    player.update();
    player.checkMapCollisions(background);
    radar.update(&player);
    shield.setPosition(player.getCenter());

    if (pressed.shield)
        shield.activate(true);
    else
        shield.activate(false);

    healthBar.manageHover(sf::Mouse::getPosition());
    energyBar.manageHover(sf::Mouse::getPosition());

    healthBar.move(player.getMoveBy());
    energyBar.move(player.getMoveBy());

    radar.move(player.getMoveBy());

    crosshairPlayer.move(player.getMoveBy());
    crosshairShip.move(player.getMoveBy());

    crosshairPlayer.move(moveCross().first);
    crosshairShip.move(moveCross().second);
}

void PlayerUI::display(sf::RenderWindow *window)
{
    view.setCenter(player.getGlobalBounds().getCenter());
    window->setView(view);
    window->draw(*background);
    window->draw(player);
    window->draw(*player2);
    window->draw(radar);
    if (shield.isActive())
        window->draw(shield);

    for (auto& i : player.getMissileManager()->getMissiles())
        window->draw(*i);
    for (auto& i : player2->getMissileManager()->getMissiles())
        window->draw(*i);

    
    window->draw(crosshairPlayer);
    window->draw(crosshairShip);
    window->draw(healthBar);
    window->draw(energyBar);
}

void PlayerUI::crosshairHandleEvents(const std::optional<sf::Event>& ev)
{
    if (const auto* keyPressed = ev->getIf<sf::Event::KeyPressed>())
    {
        if (keyPressed->code == keyBinds.crossUp)
            pressed.upCross = true;
        if (keyPressed->code == keyBinds.crossDown)
            pressed.downCross = true;
        if (keyPressed->code == keyBinds.crossLeft)
            pressed.leftCross = true;
        if (keyPressed->code == keyBinds.crossRight)
            pressed.rightCross = true;
    }

    if (const auto* keyReleased = ev->getIf<sf::Event::KeyReleased>())
    {
        if (keyReleased->code == keyBinds.crossUp)
            pressed.upCross = false;
        if (keyReleased->code == keyBinds.crossDown)
            pressed.downCross = false;
        if (keyReleased->code == keyBinds.crossLeft)
            pressed.leftCross = false;
        if (keyReleased->code == keyBinds.crossRight)
            pressed.rightCross = false;
    }
}

std::pair<sf::Vector2f, sf::Vector2f> PlayerUI::moveCross()
{
    sf::Vector2f moveCross;
    if (pressed.upCross)
        moveCross.y -= 0.5f;
    if (pressed.downCross)
        moveCross.y += 0.5f;
    if (pressed.leftCross)
        moveCross.x -= 0.5f;
    if (pressed.rightCross)
        moveCross.x += 0.5f;

    //check kolizji
    if (crosshairPlayer.getPosition().x > player.getPosition().x + view.getSize().x / 2.f)
        crosshairPlayer.setPosition({player.getPosition().x + view.getSize().x / 2.f, crosshairPlayer.getPosition().y});
    if (crosshairPlayer.getPosition().x < player.getPosition().x - view.getSize().x / 2.f + crosshairPlayer.getGlobalBounds().size.x)
        crosshairPlayer.setPosition({player.getPosition().x - view.getSize().x / 2.f + crosshairPlayer.getGlobalBounds().size.x, crosshairPlayer.getPosition().y});
    if (crosshairPlayer.getPosition().y > player.getPosition().y + view.getSize().y / 2.f)
        crosshairPlayer.setPosition({crosshairPlayer.getPosition().x, player.getPosition().y + view.getSize().y / 2.f});
    if (crosshairPlayer.getPosition().y < player.getPosition().y - view.getSize().y / 2.f + crosshairPlayer.getGlobalBounds().size.y * 2.f)
        crosshairPlayer.setPosition({crosshairPlayer.getPosition().x, player.getPosition().y - view.getSize().y / 2.f + crosshairPlayer.getGlobalBounds().size.y * 2.f});
    
    sf::Vector2f moveCrossShip {crosshairPlayer.getPosition().x - crosshairShip.getPosition().x, crosshairPlayer.getPosition().y - crosshairShip.getPosition().y};
    
    moveCrossShip.x = moveCrossShip.x * crosshairShipSpeed;
    moveCrossShip.y = moveCrossShip.y * crosshairShipSpeed;
    
    return {moveCross, moveCrossShip};
}
