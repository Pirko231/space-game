#include "player.hpp"

Player::Player()
{   
    turret.setTexture(util::AssetLoader::get().turret);
    turret.setRotation(-90.f);
    turret.setScale(0.12f,0.12f);
    turret.setOrigin(turret.getGlobalBounds().width / 2.f, turret.getGlobalBounds().height / 2.f);

    crosshairPlayer.setTexture(util::AssetLoader::get().pCrosshair);
    crosshairPlayer.setScale(0.04f,0.04f);
    crosshairShip.setTexture(util::AssetLoader::get().sCrosshair);
    crosshairShip.setScale(0.04f,0.04f);

#if DEVINFO
    //devInfo.font.loadFromFile("resources/fonts/defaultFont.ttf");
    devInfo.speed.setFont(util::AssetLoader::get().font);
    devInfo.pos.setFont(util::AssetLoader::get().font);
    devInfo.turretRotation.setFont(util::AssetLoader::get().font);
    //pozycja ustawiana w Player::setPosition()
    devInfo.pos.setPosition(getPosition());
    devInfo.speed.setPosition(50.f,20.f);
    devInfo.turretRotation.setPosition(50.f, 40.f);
#endif
}

Player::Player(const sf::Texture &texture, const PlayerKeyBinds &keyBinds) : Player{}
{
    setTexture(texture);

    setKeyBinds(keyBinds);
}

void Player::handleEvents(const sf::Event& ev)
{
    if (ev.type == sf::Event::KeyPressed)
    {
        if (ev.key.code == up)
            pressed.w = true;
        if (ev.key.code == down)
            pressed.s = true;
        if (ev.key.code == left)
            pressed.a = true;
        if (ev.key.code == right)
            pressed.d = true;

        if (ev.key.code == crossUp)
            pressed.upCross = true;
        if (ev.key.code == crossDown)
            pressed.downCross = true;
        if (ev.key.code == crossLeft)
            pressed.leftCross = true;
        if (ev.key.code == crossRight)
            pressed.rightCross = true;
    }

    if (ev.type == sf::Event::KeyReleased)
    {
        if (ev.key.code == up)
            pressed.w = false;
        if (ev.key.code == down)
            pressed.s = false;
        if (ev.key.code == left)
            pressed.a = false;
        if (ev.key.code == right)
            pressed.d = false;

        if (ev.key.code == crossUp)
            pressed.upCross = false;
        if (ev.key.code == crossDown)
            pressed.downCross = false;
        if (ev.key.code == crossLeft)
            pressed.leftCross = false;
        if (ev.key.code == crossRight)
            pressed.rightCross = false;

        if (ev.key.code == shoot)
        {
            LaserFactory factory{};
            missileManager.create(factory, getPosition(), crosshairShip.getPosition());
        }
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
        crosshairPlayer.setPosition(getPosition().x + view->getSize().x / 2.f, crosshairPlayer.getPosition().y);
    if (crosshairPlayer.getPosition().x < getPosition().x - view->getSize().x / 2.f + crosshairPlayer.getGlobalBounds().width)
        crosshairPlayer.setPosition(getPosition().x - view->getSize().x / 2.f + crosshairPlayer.getGlobalBounds().width, crosshairPlayer.getPosition().y);
    if (crosshairPlayer.getPosition().y > getPosition().y + view->getSize().y / 2.f)
        crosshairPlayer.setPosition(crosshairPlayer.getPosition().x, getPosition().y + view->getSize().y / 2.f);
    if (crosshairPlayer.getPosition().y < getPosition().y - view->getSize().y / 2.f + crosshairPlayer.getGlobalBounds().height * 2.f)
        crosshairPlayer.setPosition(crosshairPlayer.getPosition().x, getPosition().y - view->getSize().y / 2.f + crosshairPlayer.getGlobalBounds().height * 2.f);
    
    sf::Vector2f moveCrossShip {crosshairPlayer.getPosition().x - crosshairShip.getPosition().x, crosshairPlayer.getPosition().y - crosshairShip.getPosition().y};
    
    moveCrossShip.x = moveCrossShip.x * crosshairShipSpeed;
    moveCrossShip.y = moveCrossShip.y * crosshairShipSpeed;
    
    return {moveCross, moveCrossShip};
}

float Player::spinTurret()
{
    sf::Vector2f vector{crosshairShip.getPosition().x - turret.getPosition().x,turret.getPosition().y - crosshairShip.getPosition().y};

    float result {std::tan(vector.y / vector.x) *  180.f / (float)M_PI};
    return result;
}

void Player::rotate(float angle)
{
    sprite.setOrigin(sprite.getGlobalBounds().width / 2.f, sprite.getGlobalBounds().height / 2.f);
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
