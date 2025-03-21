#pragma once

#include <SFML/Graphics.hpp>
#include "pressed.hpp"

#ifdef MEMTRACKER
#include "../perf/memTracker.hpp"
#endif

class Player : public sf::Drawable
{
public:
    Player(const std::string& textureFilename, sf::Keyboard::Key up, sf::Keyboard::Key down, sf::Keyboard::Key left, sf::Keyboard::Key right);

    void handleEvents(const sf::Event&);

    void update();

    sf::Vector2f getCenter() const
    {
        const auto bounds = sprite.getGlobalBounds();
        return {bounds.left + bounds.width / 2.f, bounds.top + bounds.height / 2.f};
    }

    sf::Vector2f getPosition() const {return sprite.getPosition();}

    void setPosition(sf::Vector2f pos) {sprite.setPosition(pos);}
private:
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override
    {
        target.draw(sprite, states);
    }

    sf::Keyboard::Key up;
    sf::Keyboard::Key down;
    sf::Keyboard::Key left;
    sf::Keyboard::Key right;

    Pressed pressed;

    sf::Vector2f moveBy{0.f,0.f};

    float throttle{0.02f};

    float maxSpeed{6.5f};

    sf::Sprite sprite;
    sf::Texture mainTexture;

    #if DEVINFO
public:
    const sf::Drawable& getStats() const {return devInfo;}
    void setStatsPos(sf::Vector2f _pos)
    {
        devInfo.defaultPos = _pos;
        devInfo.pos.setPosition(devInfo.defaultPos);
        devInfo.speed.setPosition(devInfo.defaultPos.x, devInfo.defaultPos.y + 20.f);
        devInfo.pos.setCharacterSize(20);
        devInfo.speed.setCharacterSize(20);
    }
private:
    struct DevInfo : public sf::Drawable
    {
        DevInfo(const Player* _player) {player = _player;}
        sf::Font font;
        mutable sf::Text pos;
        mutable sf::Text speed;
        sf::Vector2f defaultPos;
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
        }
    }; DevInfo devInfo{this};
    #endif
};