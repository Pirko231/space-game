#include "player.hpp"

Player::Player(const sf::Texture& texture, Pressed& _pressed)
: sprite{texture}, turret{util::AssetLoader::get().turret}, keys{_pressed}, missileManager{keyBinds}
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
    if (destroyed)
        return;

    missileManager.handleEvents(keys);
}

void Player::update()
{
    missileManager.update(&rocketRecentlyDeleted);

    
    if (health <= 0 && !destroyed)
        destroy();

    if (destroyed)
    {
        explosion.update();
        explosion.setPosition(getCenter());
        return;
    }
    
    //tarcza
    shield.setPosition(getCenter());
    if (keys[keyBinds.shield].pressed && energy >= shield.getEnergyUse())
    {
        shield.activate(true);
        temperature += 4 * util::ConfigLoader::get().temperatureDoubler;
    }
    else
        shield.activate(false);

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

    temperature -= 5 * util::ConfigLoader::get().temperatureDoubler;
    if (temperature < -60)
        temperature = -60;
    if (temperature > 4000)
        temperature = 4000;

    move(moveBy);
    
    //kiedy jest rakieta to nie aktualizujemy gracza
    if (missileManager.getRocket().has_value())
        return;
    
    //ruch
    if (keys[keyBinds.up].pressed && moveBy.y > -maxSpeed)
    {
        sf::Vector2f add{0.f, -throttle};
        add = add.rotatedBy(sprite.getRotation());
        moveBy += add;
        temperature += 6 * util::ConfigLoader::get().temperatureDoubler;
    }
    if (keys[keyBinds.down].pressed)
    {
        sf::Vector2f add{0.f, throttle};
        add = add.rotatedBy(sprite.getRotation());
        moveBy += add;
        temperature += 6 * util::ConfigLoader::get().temperatureDoubler;
    }
    if (keys[keyBinds.left].pressed)
    {
        rotate(-rotationSpeed);
        temperature += 4 * util::ConfigLoader::get().temperatureDoubler;
    }
    if (keys[keyBinds.right].pressed)
    {
        rotate(rotationSpeed);
        temperature += 4 * util::ConfigLoader::get().temperatureDoubler;
    }

    if (shield.isActive())
        energy -= shield.getEnergyUse();
    
    if (energy <= maxEnergy)
        energy += energyRefill;

    turret.setRotation(spinTurret());
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

void Player::destroy()
{
    destroyed = true;
    temperature = 4000;
    moveBy = {0.f,0.f};
    if (missileManager.getRocket().has_value())
        const_cast<std::optional<Rocket*>&>(missileManager.getRocket()).reset();
    shield.activate(false);

    explosion.setPosition(getCenter());
    explosion.playSound();
}
