#pragma once
#include <SFML/Graphics.hpp>
#include <span>
#include "assetLoader.hpp"
#include "missileFactory.hpp"
#include "factories/laserFactory.hpp"
#include "factories/rocketFactory.hpp"
#include "factories/mineFactory.hpp"
#include "timer.hpp"

struct MissilePicker : public sf::Drawable
{
    MissilePicker();
    
    void setPosition(sf::Vector2f pos);
    
    void move(sf::Vector2f offset) {setPosition(getPosition() + offset);}

    void right();
    void left();

    void setRocketCooldown(int cooldown)
    {
        int rocketCooldown = util::framesToSeconds(cooldown);
        if (rocketCooldown > 0)
            rocketTimer.setString(std::to_string(rocketCooldown));
        else
            rocketTimer.setString('R');
    }

    void setMineCooldown(int cooldown)
    {
        int mineCooldown = util::framesToSeconds(cooldown);
        if (mineCooldown > 0)
            mineTimer.setString(std::to_string(mineCooldown));
        else
            mineTimer.setString('R');
    }

    IMissileFactory& getCurrentMissile() {return *factories[currentFactory];}

    sf::Vector2f getPosition() const {return sprites.begin()->getPosition();}
    sf::FloatRect getGlobalBounds() const {return sf::FloatRect{{sprites.begin()->getPosition()}, {sprites.begin()->getSize().x * 3.f, sprites.begin()->getSize().y}};}
    ~MissilePicker() {delete[] spritesArr;}
private:
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override
    {
        for (auto& i : sprites)
            target.draw(i, states);
        for (auto& i : missiles)
            target.draw(i, states);
        target.draw(rocketTimer, states);
        target.draw(mineTimer, states);
    }

    float defaultThickness{1.f};
    float underlinedThickness{2.f};
   
    sf::RectangleShape current;
    sf::RectangleShape* spritesArr{};
    std::span<sf::RectangleShape>sprites;
    sf::Sprite missileTextures[3] {sf::Sprite{util::AssetLoader::get().laser}, sf::Sprite{util::AssetLoader::get().rocket}, sf::Sprite{util::AssetLoader::get().mine}};
    std::span<sf::Sprite>missiles;

    static constexpr int amount{3};
    int currentFactory{};
    LaserFactory laserFactory;
    RocketFactory rocketFactory;
    MineFactory mineFactory;
    IMissileFactory* factories[amount]{&laserFactory, &rocketFactory, &mineFactory};

    sf::Text rocketTimer{util::AssetLoader::get().font};
    sf::Text mineTimer{util::AssetLoader::get().font};
};