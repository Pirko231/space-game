#pragma once

#include <SFML/Graphics.hpp>
#include <cmath>
#include "pressed.hpp"
#include "assetLoader.hpp"
#include "../gameObjects/managers/missileManager.hpp"

struct PlayerKeyBinds
{
    sf::Keyboard::Key up, down, left, right;
    sf::Keyboard::Key crossUp, crossDown, crossLeft, crossRight;
};

class Player : public sf::Drawable
{
public:
    //Player(const std::string& textureFilename, sf::Keyboard::Key up, sf::Keyboard::Key down, sf::Keyboard::Key left, sf::Keyboard::Key right);

    Player();
    Player(const sf::Texture &texture, const PlayerKeyBinds& keyBinds);
    
    void handleEvents(const sf::Event&);

    void update();

    void setView(const sf::View* _view) {view = _view;}

    void setTexture(const sf::Texture& texture)
    {
        sprite.setTexture(texture);
        sprite.setScale(0.1f,0.1f);
    }

    void setKeyBinds(const PlayerKeyBinds& keyBinds)
    {
        up = keyBinds.up;
        down = keyBinds.down;
        left = keyBinds.left;
        right = keyBinds.right;

        crossUp = keyBinds.crossUp;
        crossDown = keyBinds.crossDown;
        crossLeft = keyBinds.crossLeft;
        crossRight = keyBinds.crossRight;
    }

    sf::Vector2f getCenter() const
    {
        const auto bounds = sprite.getGlobalBounds();
        return {bounds.left + bounds.width / 2.f, bounds.top + bounds.height / 2.f};
    }

    sf::Vector2f getPosition() const {return sprite.getPosition();}

    sf::FloatRect getGlobalBounds() const {return sprite.getGlobalBounds();}

    const MissileManager* getMissileManager() const {return &missileManager;}

    const sf::Sprite* getHitbox() const {return &sprite;}

    void setPosition(sf::Vector2f pos) 
    {
        sprite.setOrigin(sprite.getGlobalBounds().width / 2.f, sprite.getGlobalBounds().height / 2.f);
        sprite.setPosition(pos);
        turret.setOrigin(turret.getGlobalBounds().width / 4.f, turret.getGlobalBounds().height / 2.f);
        //turret.setPosition(pos.x + turret.getGlobalBounds().width / 1.9f, pos.y + 15.f);
        turret.setPosition(pos.x + turret.getGlobalBounds().width / 1.5f, pos.y + turret.getGlobalBounds().height / 1.8f);
        crosshairPlayer.setPosition(pos.x + sprite.getGlobalBounds().width / 2.f, pos.y - sprite.getGlobalBounds().height);
        crosshairShip.setPosition(crosshairPlayer.getPosition());
    }
private:
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override
    {
        target.draw(sprite, states);
        target.draw(turret, states);
        target.draw(crosshairPlayer);
        target.draw(crosshairShip);
    }

    const sf::View* view;

    //first - pozycja playerCrosshair
    //second - pozycja shipCrosshair
    std::pair<sf::Vector2f, sf::Vector2f> moveCross();

    float spinTurret();

    void rotate(float angle);

    void move(sf::Vector2f offset);

    sf::Keyboard::Key up, crossUp;
    sf::Keyboard::Key down, crossDown;
    sf::Keyboard::Key left, crossLeft;
    sf::Keyboard::Key right, crossRight;

    Pressed pressed;

    MissileManager missileManager;

    sf::Vector2f moveBy{0.f,0.f};

    float throttle{0.02f};

    float maxSpeed{6.5f};

    sf::Sprite sprite;

    sf::Sprite turret;

    sf::Sprite crosshairPlayer;
    sf::Sprite crosshairShip;

    static constexpr float crosshairShipSpeed{0.02f};

    #if DEVINFO
public:
    const sf::Drawable& getStats() const {return devInfo;}
    void setStatsPos(sf::Vector2f _pos) const
    {
        devInfo.defaultPos = _pos;
        devInfo.pos.setPosition(devInfo.defaultPos);
        devInfo.speed.setPosition(devInfo.defaultPos.x, devInfo.defaultPos.y + 20.f);
        devInfo.turretRotation.setPosition(devInfo.defaultPos.x, devInfo.defaultPos.y + 40.f);
        devInfo.pos.setCharacterSize(20);
        devInfo.speed.setCharacterSize(20);
        devInfo.turretRotation.setCharacterSize(20);
    }
private:
    struct DevInfo : public sf::Drawable
    {
        DevInfo(const Player* _player) {player = _player;}
        mutable sf::Text pos;
        mutable sf::Text speed;
        mutable sf::Text turretRotation;
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
            sf::String turretRotationString {std::to_string(player->turret.getRotation())};
            turretRotation.setString(turretRotationString);
            target.draw(turretRotation, states);
        }
    }; DevInfo devInfo{this};
    #endif
};