#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <cmath>
#include "pressed.hpp"
#include "assetLoader.hpp"
#include "configLoader.hpp"
#include "shield.hpp"
#include "../gameObjects/managers/missileManager.hpp"
#include "map.hpp"

class Player : public sf::Drawable
{
public:
    Player(const sf::Texture& texture, Pressed&);
    Player(const sf::Texture &texture, const PlayerKeyBinds& keyBinds, Pressed& _pressed);
    
    void handleEvents(const std::optional<sf::Event>& ev);

    void update();

    void setView(const sf::View* _view) {view = _view;}

    void setPosition(sf::Vector2f pos) 
    {
        sprite.setPosition(pos);
        turret.setOrigin(turret.getGlobalBounds().getCenter());
        turret.setPosition({pos.x + turret.getGlobalBounds().size.x / 1.5f, pos.y + turret.getGlobalBounds().size.y / 1.8f});
    }

    void setTexture(const sf::Texture& texture)
    {
        sprite.setTexture(texture);
        sprite.setScale({0.1f,0.1f});
    }

    void setKeyBinds(const PlayerKeyBinds& _keyBinds)
    {
        keyBinds = _keyBinds;
    }

    sf::Vector2f getCenter() const
    {
        return sprite.getGlobalBounds().getCenter();
    }

    void damaged(int damage) const
    {
        if (shield.isActive())
            (damage - shield.getDamageResistance() < 0) ? (damage = 1) : (damage -= shield.getDamageResistance());
        health -= damage;
    }

    void shoot(IMissileFactory& factoryType, sf::Vector2f crosshairPos)
    {
        if (energy >= factoryType.cost())
        {
            if (missileManager.create(factoryType, getGlobalBounds().getCenter(), crosshairPos))
                energy -= factoryType.cost();
        }
    }

    bool rocketDeleted() { if(rocketRecentlyDeleted){rocketRecentlyDeleted = false; return true;}return false;}

    sf::Vector2f getPosition() const {return sprite.getPosition();}

    sf::FloatRect getGlobalBounds() const {return sprite.getGlobalBounds();}

    sf::Vector2f getMoveBy() const
    {
        if (!missileManager.getRocket().has_value())
            return moveBy;
        return missileManager.getRocket().value()->getMoveBy();
    }

    int getTemperature() const {return temperature;}

    const MissileManager* getMissileManager() const {return &missileManager;}

    const sf::Sprite* getHitbox() const {return &sprite;}

    float* getHealth() const {return &health;}
    float* getEnergy() const {return &energy;}

    bool checkMapCollisions(Map* map);
private:
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override
    {
        target.draw(sprite, states);
        target.draw(turret, states);
        if (shield.isActive())
            target.draw(shield, states);
    }

    const sf::View* view;

    sf::Angle spinTurret();

    void rotate(sf::Angle angle);

    void move(sf::Vector2f offset);

    MissileManager missileManager;

    sf::Vector2f moveBy{0.f,0.f};

    int temperature{};

    float throttle{util::ConfigLoader::get().throttle};

    float maxSpeed{3.5f};

    sf::Angle rotationSpeed{util::ConfigLoader::get().shipRotationSpeed};

    mutable float health{util::ConfigLoader::get().health};
    mutable float energy{util::ConfigLoader::get().energy};
    float maxEnergy{util::ConfigLoader::get().energy};
    float energyRefill{util::ConfigLoader::get().energyRefill};

    bool rocketRecentlyDeleted{};

    sf::Sprite sprite;

    sf::Sprite turret;

    PlayerKeyBinds keyBinds;

    Pressed& pressed;

    Shield shield;

    #if DEVINFO
public:
    const sf::Drawable& getStats() const {return devInfo;}
    void setStatsPos(sf::Vector2f _pos) const
    {
        devInfo.defaultPos = _pos;
        devInfo.pos.setPosition(devInfo.defaultPos);
        devInfo.speed.setPosition(sf::Vector2f{devInfo.defaultPos.x, devInfo.defaultPos.y + 20.f});
        devInfo.turretRotation.setPosition({devInfo.defaultPos.x, devInfo.defaultPos.y + 40.f});
        devInfo.pos.setCharacterSize(20);
        devInfo.speed.setCharacterSize(20);
        devInfo.turretRotation.setCharacterSize(20);
    }
private:
    struct DevInfo : public sf::Drawable
    {
        DevInfo(const Player* _player) {player = _player;}
        mutable sf::Text pos{util::AssetLoader::get().font};
        mutable sf::Text speed{util::AssetLoader::get().font};
        mutable sf::Text turretRotation{util::AssetLoader::get().font};
        mutable sf::Vector2f defaultPos;
    private:
        const Player* player{nullptr};
        void draw(sf::RenderTarget& target, sf::RenderStates states) const override
        {
            sf::String posString {std::to_string(player->getPosition().x) + ' ' + std::to_string(player->getPosition().y)};
            pos.setString(posString);
            target.draw(pos, states);
            sf::String speedString {std::to_string(player->moveBy.x) + ' ' + std::to_string(player->moveBy.y)};
            speed.setString(speedString);
            target.draw(speed, states);
            sf::String turretRotationString {std::to_string(player->turret.getRotation().asDegrees())};
            turretRotation.setString(turretRotationString);
            target.draw(turretRotation, states);
        }
    }; DevInfo devInfo{this};
    #endif
};