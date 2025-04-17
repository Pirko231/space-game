#include "player.hpp"

Player::Player(const sf::Texture& texture)
: sprite{texture}, turret{util::AssetLoader::get().turret}, crosshairPlayer{util::AssetLoader::get().pCrosshair}, crosshairShip{util::AssetLoader::get().sCrosshair}
{   
    sprite.setOrigin(sprite.getGlobalBounds().getCenter());
    turret.setTexture(util::AssetLoader::get().turret);
    turret.setRotation(sf::degrees(-90.f));
    turret.setScale({0.12f,0.12f});
    turret.setOrigin(turret.getGlobalBounds().getCenter());

    crosshairPlayer.setScale({0.04f,0.04f});
    crosshairShip.setScale({0.04f,0.04f});

#if DEVINFO
    //devInfo.font.loadFromFile("resources/fonts/defaultFont.ttf");
    devInfo.speed.setFont(util::AssetLoader::get().font);
    devInfo.pos.setFont(util::AssetLoader::get().font);
    devInfo.turretRotation.setFont(util::AssetLoader::get().font);
    //pozycja ustawiana w Player::setPosition()
    devInfo.pos.setPosition(getPosition());
    devInfo.speed.setPosition({50.f,20.f});
    devInfo.turretRotation.setPosition({50.f, 40.f});
#endif
}

Player::Player(const sf::Texture &texture, const PlayerKeyBinds &keyBinds) : Player{texture}
{
    setTexture(texture);

    setKeyBinds(keyBinds);
}

void Player::handleEvents(const std::optional<sf::Event>& ev)
{
    if (const auto* keyPressed = ev->getIf<sf::Event::KeyPressed>())
    {
        if (keyPressed->code == keyBinds.up)
            pressed.w = true;
        if (keyPressed->code == keyBinds.down)
            pressed.s = true;
        if (keyPressed->code == keyBinds.left)
            pressed.a = true;
        if (keyPressed->code == keyBinds.right)
            pressed.d = true;

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
        if (keyReleased->code == keyBinds.up)
            pressed.w = false;
        if (keyReleased->code == keyBinds.down)
            pressed.s = false;
        if (keyReleased->code == keyBinds.left)
            pressed.a = false;
        if (keyReleased->code == keyBinds.right)
            pressed.d = false;

        if (keyReleased->code == keyBinds.crossUp)
            pressed.upCross = false;
        if (keyReleased->code == keyBinds.crossDown)
            pressed.downCross = false;
        if (keyReleased->code == keyBinds.crossLeft)
            pressed.leftCross = false;
        if (keyReleased->code == keyBinds.crossRight)
            pressed.rightCross = false;

        if (keyReleased->code == keyBinds.shoot)
            missileManager.create(LaserFactory{}.get(), getGlobalBounds().getCenter(), crosshairShip.getPosition());
        
    }
}

void Player::update()
{
    if (pressed.w && moveBy.y > -maxSpeed)
    {
        moveBy.y -= throttle;
    }
    if (pressed.s && moveBy.y < (maxSpeed / 2.f))
    {
        moveBy.y += throttle / 2.5f;
        if (moveBy.y < 0)
            moveBy.y += throttle;
    }
    if (pressed.a)
    {
        moveBy.x -= throttle / 2.f;
    }
    if (pressed.d)
    {
        moveBy.x += throttle / 2.f;
    }

    if (moveBy.y > 0)
        moveBy.y -= throttle / 5.f;
    if (moveBy.y < 0)
        moveBy.y += throttle / 5.f;
    if (moveBy.x > 0)
        moveBy.x -= throttle / 7.f;
    if (moveBy.x < 0)
        moveBy.x += throttle / 7.f;

    move(moveBy);

    std::pair<sf::Vector2f, sf::Vector2f> moveCrossBy {moveCross()};
    crosshairPlayer.move(moveCrossBy.first);
    crosshairShip.move(moveCrossBy.second);

    turret.setRotation(spinTurret());

    missileManager.update();
}

std::pair<sf::Vector2f, sf::Vector2f> Player::moveCross()
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
    if (crosshairPlayer.getPosition().x > getPosition().x + view->getSize().x / 2.f)
        crosshairPlayer.setPosition({getPosition().x + view->getSize().x / 2.f, crosshairPlayer.getPosition().y});
    if (crosshairPlayer.getPosition().x < getPosition().x - view->getSize().x / 2.f + crosshairPlayer.getGlobalBounds().size.x)
        crosshairPlayer.setPosition({getPosition().x - view->getSize().x / 2.f + crosshairPlayer.getGlobalBounds().size.x, crosshairPlayer.getPosition().y});
    if (crosshairPlayer.getPosition().y > getPosition().y + view->getSize().y / 2.f)
        crosshairPlayer.setPosition({crosshairPlayer.getPosition().x, getPosition().y + view->getSize().y / 2.f});
    if (crosshairPlayer.getPosition().y < getPosition().y - view->getSize().y / 2.f + crosshairPlayer.getGlobalBounds().size.y * 2.f)
        crosshairPlayer.setPosition({crosshairPlayer.getPosition().x, getPosition().y - view->getSize().y / 2.f + crosshairPlayer.getGlobalBounds().size.y * 2.f});
    
    sf::Vector2f moveCrossShip {crosshairPlayer.getPosition().x - crosshairShip.getPosition().x, crosshairPlayer.getPosition().y - crosshairShip.getPosition().y};
    
    moveCrossShip.x = moveCrossShip.x * crosshairShipSpeed;
    moveCrossShip.y = moveCrossShip.y * crosshairShipSpeed;
    
    return {moveCross, moveCrossShip};
}

sf::Angle Player::spinTurret()
{
    sf::Vector2f vector{crosshairShip.getPosition().x - turret.getPosition().x,turret.getPosition().y - crosshairShip.getPosition().y};
    return sf::radians(std::tan(vector.y / vector.x));
}

void Player::rotate(sf::Angle angle)
{
    sprite.setOrigin(sprite.getGlobalBounds().getCenter());
    sprite.rotate(angle);
    turret.rotate(angle);
}

void Player::move(sf::Vector2f offset)
{
    sprite.move(offset);
    turret.move(offset);
    crosshairPlayer.move(offset);
    crosshairShip.move(offset);
}
