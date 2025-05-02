#include "playerUI.hpp"

sf::RenderWindow* PlayerUI::window {nullptr};

PlayerUI::PlayerUI()
: player{util::AssetLoader::get().ship1, pressed}, healthBar{player.getHealth(), 0, static_cast<int>(*player.getHealth())}, energyBar{player.getEnergy(), 0, static_cast<int>(*player.getEnergy())},
  crosshairPlayer{util::AssetLoader::get().pCrosshair}, crosshairShip{util::AssetLoader::get().sCrosshair}
{
    player.setView(&view);

    healthBar.setColor(sf::Color::Red);
    energyBar.setColor(sf::Color::Blue);

    crosshairPlayer.setScale({0.04f,0.04f});
    crosshairShip.setScale({0.04f,0.04f});

    crosshairPos = {player.getCenter().x, player.getCenter().y + crosshairRadius};
    crosshairPlayer.setPosition({player.getCenter().x, player.getCenter().y + crosshairRadius});
}

void PlayerUI::handleEvents(const std::optional<sf::Event>& ev)
{
    player.handleEvents(ev);

    crosshairHandleEvents(ev);

    if (const auto* keyPressed = ev->getIf<sf::Event::KeyPressed>())
    {
        if (keyPressed->code == keyBinds.shield)
            pressed.shield = true;
        if (keyPressed->code == keyBinds.scanner)
            pressed.scanner = true;
        
    }
    
    if (const auto* keyReleased = ev->getIf<sf::Event::KeyReleased>())
    {
        if (keyReleased->code == keyBinds.shoot)
        {
            player.shoot(missilePicker.getCurrentMissile(), crosshairShip.getPosition());
            player.getMissileManager()->handleEvents(pressed);
        }
        if (keyReleased->code == keyBinds.shield)
            pressed.shield = false;
        if (keyReleased->code == keyBinds.scanner)
            pressed.scanner = false;

        if (keyReleased->code == keyBinds.weaponLeft)
            missilePicker.left();
        if (keyReleased->code == keyBinds.weaponRight)
            missilePicker.right();
    }

}

void PlayerUI::update()
{
    player.update();
    player.checkMapCollisions(background);
    updateRadar();

    if (player.rocketDeleted())
        setPlayerPos(player.getCenter());
    

    healthBar.manageHover(sf::Mouse::getPosition());
    energyBar.manageHover(sf::Mouse::getPosition());

    healthBar.move(player.getMoveBy());
    energyBar.move(player.getMoveBy());

    radar.move(player.getMoveBy());
    missilePicker.move(player.getMoveBy());

    managePlayerCross();

    moveCrosshairShip();

    missilePicker.setRocketCooldown(player.getMissileManager()->getRocketCooldown());
    missilePicker.setMineCooldown(player.getMissileManager()->getMineCooldown());
}

void PlayerUI::display(sf::RenderWindow *window)
{
    if (player.getMissileManager()->getRocket().has_value())
        view.setCenter(player.getMissileManager()->getRocket().value()->getGlobalBounds().getCenter());
    else
        view.setCenter(player.getGlobalBounds().getCenter());
    window->setView(view);
    window->draw(*background);
    window->draw(player);
    window->draw(*player2);
    window->draw(radar);
    if (player.getMissileManager()->getRocket().has_value())
        window->draw(player.getMissileManager()->getRocketTimer());
    if (!player.getMissileManager()->getRocket().has_value())
        window->draw(missilePicker);
    

    for (auto& i : player.getMissileManager()->getMissiles())
        window->draw(*i);
    for (auto& i : player2->getMissileManager()->getMissiles())
        window->draw(*i);

    if (!player.getMissileManager()->getRocket().has_value())
    {
        window->draw(crosshairPlayer);
        window->draw(crosshairShip);
        window->draw(healthBar);
        window->draw(energyBar);
    }
}

void PlayerUI::updateRadar()
{
    radar.setDefault();
    if (pressed.scanner && *player.getEnergy() > scanner.getEnergyUse())
    {
        *player.getEnergy() -= scanner.getEnergyUse();
        radar.setRange(scanner.getRange(), scanner.getRectSize());
    }
    if (player.getMissileManager()->getRocket().has_value())
        radar.update(&player, player.getMissileManager()->getRocket().value()->getGlobalBounds().getCenter());
    else
        radar.update(&player);
}

void PlayerUI::crosshairHandleEvents(const std::optional<sf::Event> &ev)
{
    if (const auto* keyPressed = ev->getIf<sf::Event::KeyPressed>())
    {
        if (keyPressed->code == keyBinds.crossLeft)
            pressed.leftCross = true;
        if (keyPressed->code == keyBinds.crossRight)
            pressed.rightCross = true;
    }

    if (const auto* keyReleased = ev->getIf<sf::Event::KeyReleased>())
    {
        if (keyReleased->code == keyBinds.crossLeft)
            pressed.leftCross = false;
        if (keyReleased->code == keyBinds.crossRight)
            pressed.rightCross = false;
    }
}

void PlayerUI::moveCrosshairShip()
{   
    sf::Vector2f moveCrossShip {crosshairPlayer.getPosition().x - crosshairShip.getPosition().x, crosshairPlayer.getPosition().y - crosshairShip.getPosition().y};
    
    moveCrossShip.x = moveCrossShip.x * crosshairShipSpeed;
    moveCrossShip.y = moveCrossShip.y * crosshairShipSpeed;
    
    crosshairShip.move(moveCrossShip);
    crosshairShip.move(player.getMoveBy());
}

void PlayerUI::managePlayerCross()
{
    sf::Vector2f moveCross{};
    if (crosshairPos.x - player.getCenter().x < 0.f)
    {
        if (crosshairPos.y - player.getCenter().y < 0)
        {
            if (pressed.leftCross)
                moveCross += {-1.f, 1.f};
            if (pressed.rightCross)
                moveCross += {1.f, -1.f};
        }
        else
        {
            if (pressed.leftCross)
                moveCross += {1.f, 1.f};
            if (pressed.rightCross)
                moveCross -= {1.f, 1.f};
        }    
    }
    else
    {
        if (crosshairPos.y - player.getCenter().y < 0)
        {
            if (pressed.leftCross)
                moveCross += {-1.f, -1.f};
            if (pressed.rightCross)
                moveCross += {1.f, 1.f};
        }
        else
        {
            if (pressed.leftCross)
                moveCross += {1.f, -1.f};
            if (pressed.rightCross)
                moveCross += {-1.f, 1.f};
        }
    }
    if (moveCross != sf::Vector2f{})
        moveCross = moveCross.normalized();

    crosshairPos = player.getCenter() + sf::Vector2f{crosshairPos + moveCross - player.getCenter()}.normalized() * crosshairRadius;
    
    crosshairPos += player.getMoveBy();
    crosshairPlayer.setPosition(crosshairPos);
}
