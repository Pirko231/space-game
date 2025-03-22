#include "player.hpp"

Player::Player(const std::string &textureFilename, const PlayerKeyBinds &keyBinds)
{
    mainTexture.loadFromFile(textureFilename);
    sprite.setTexture(mainTexture);

    crosshairPlayerTxt.loadFromFile("resources/textures/crosshair108.png");
    crosshairPlayer.setTexture(crosshairPlayerTxt);
    crosshairPlayer.setScale(0.04f,0.04f);
    crosshairShipTxt.loadFromFile("resources/textures/crosshair111.png");
    crosshairShip.setTexture(crosshairShipTxt);
    crosshairShip.setScale(0.04f,0.04f);

    sprite.setScale(0.1f,0.1f);
    up = keyBinds.up;
    down = keyBinds.down;
    left = keyBinds.left;
    right = keyBinds.right;

    crossUp = keyBinds.crossUp;
    crossDown = keyBinds.crossDown;
    crossLeft = keyBinds.crossLeft;
    crossRight = keyBinds.crossRight;

    #if DEVINFO
    devInfo.font.loadFromFile("resources/fonts/defaultFont.ttf");
    devInfo.speed.setFont(devInfo.font);
    devInfo.pos.setFont(devInfo.font);
    devInfo.pos.setPosition(getPosition());
    //devInfo.pos.setCharacterSize(2);
    devInfo.speed.setPosition(50.f,20.f);
    #endif
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

    if (moveBy.y > 0)
        moveBy.y -= throttle / 5.f;
    if (moveBy.y < 0)
        moveBy.y += throttle / 5.f;

    
    sprite.move(moveBy);
    crosshairPlayer.move(moveBy);
    crosshairShip.move(moveBy);

    crosshairPlayer.move(moveCross().first);
    crosshairPlayer.move(moveCross().second);
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
    if (crosshairPlayer.getPosition().x > getPosition().x + view.getSize().x / 2.f)
        crosshairPlayer.setPosition(getPosition().x + view.getSize().x / 2.f, crosshairPlayer.getPosition().y);
    if (crosshairPlayer.getPosition().x < getPosition().x - view.getSize().x / 2.f + crosshairPlayer.getGlobalBounds().width)
        crosshairPlayer.setPosition(getPosition().x - view.getSize().x / 2.f + crosshairPlayer.getGlobalBounds().width, crosshairPlayer.getPosition().y);
    if (crosshairPlayer.getPosition().y > getPosition().y + view.getSize().y / 2.f)
        crosshairPlayer.setPosition(crosshairPlayer.getPosition().x, getPosition().y + view.getSize().y / 2.f);
    if (crosshairPlayer.getPosition().y < getPosition().y - view.getSize().y / 2.f + crosshairPlayer.getGlobalBounds().height * 2.f)
        crosshairPlayer.setPosition(crosshairPlayer.getPosition().x, getPosition().y - view.getSize().y / 2.f + crosshairPlayer.getGlobalBounds().height * 2.f);
    
    return {moveCross, {0.f,0.f}};
}
