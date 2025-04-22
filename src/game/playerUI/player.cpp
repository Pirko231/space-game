#include "player.hpp"

Player::Player(const sf::Texture& texture, Pressed& _pressed)
: sprite{texture}, turret{util::AssetLoader::get().turret}, pressed{_pressed}
{   
    sprite.setOrigin(sprite.getGlobalBounds().getCenter());
    turret.setTexture(util::AssetLoader::get().turret);
    turret.setRotation(sf::degrees(-90.f));
    turret.setScale({0.12f,0.12f});
    turret.setOrigin(turret.getGlobalBounds().getCenter());

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

Player::Player(const sf::Texture &texture, const PlayerKeyBinds &keyBinds, Pressed& _pressed)
: Player{texture, _pressed}
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
    }
}

void Player::update()
{
    //tarcza
    shield.setPosition(getCenter());
    if (pressed.shield && energy >= shield.getEnergyUse())
        shield.activate(true);
    else
        shield.activate(false);
    
    //ruch
    if (pressed.w && moveBy.y > -maxSpeed)
    {
        sf::Vector2f add{0.f, -throttle};
        add = add.rotatedBy(sprite.getRotation());
        moveBy += add;
    }
    if (pressed.s)
    {
        sf::Vector2f add{0.f, throttle};
        add = add.rotatedBy(sprite.getRotation());
        moveBy += add;
        //moveBy.y += throttle / 2.5f;
        /*if (moveBy.y < 0)
            moveBy.y += throttle;*/
    }
    if (pressed.a)
    {
        rotate(sf::degrees(-1.f));
    }
    if (pressed.d)
    {
        rotate(sf::degrees(1.f));
    }

    if (moveBy.y > 0)
        moveBy.y -= throttle / 5.f;
    if (moveBy.y < 0)
        moveBy.y += throttle / 5.f;
    if (moveBy.x > 0)
        moveBy.x -= throttle / 7.f;
    if (moveBy.x < 0)
        moveBy.x += throttle / 7.f;

    if (moveBy.y >= maxSpeed)
        moveBy.y = maxSpeed;
    if (moveBy.y <= -maxSpeed)
        moveBy.y = -maxSpeed;
    if (moveBy.x >= maxSpeed)
        moveBy.x = maxSpeed;
    if (moveBy.x <= -maxSpeed)
        moveBy.x = -maxSpeed;

    move(moveBy);

    if (shield.isActive())
        energy -= shield.getEnergyUse();
    
    if (energy <= 100.f)
        energy += 0.05f;

    turret.setRotation(spinTurret());

    missileManager.update();
}

bool Player::checkMapCollisions(Map *map)
{
    sf::Vector2f playerPos{getPosition()};
    sf::FloatRect mapBounds{map->getBounds()};
    sf::Vector2f hitboxOffset{view->getSize()};
    bool collisionFound{};

    if (playerPos.x < 0)
    {
        setPosition({0.f, playerPos.y});
        moveBy.x = 0.f;
        collisionFound = true;
    }
    if (playerPos.x > mapBounds.size.x)
    {
        setPosition({mapBounds.size.x, playerPos.y});
        moveBy.x = 0.f;
        collisionFound = true;
    }
    if (playerPos.y < 0)
    {
        setPosition({playerPos.x, 0.f});
        moveBy.y = 0.f;
        collisionFound = true;
    }
    if (playerPos.y > mapBounds.size.y)
    {
        setPosition({playerPos.x, mapBounds.size.y});
        moveBy.y = 0.f;
        collisionFound = true;
    }

    return collisionFound;
}

sf::Angle Player::spinTurret()
{
    //sf::Vector2f vector{crosshairShip.getPosition().x - turret.getPosition().x,turret.getPosition().y - crosshairShip.getPosition().y};
    return sf::degrees(0.f);
}

void Player::rotate(sf::Angle angle)
{
    sprite.rotate(angle);
    
    moveBy = moveBy.rotatedBy(angle);
}

void Player::move(sf::Vector2f offset)
{
    sprite.move(offset);
    turret.move(offset);
}
