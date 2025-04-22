#pragma once
#include <SFML/Graphics.hpp>
#include <span>
#include "assetLoader.hpp"
#include "missileFactory.hpp"
#include "factories/laserFactory.hpp"
#include "factories/rocketFactory.hpp"
#include "factories/scannerFactory.hpp"

struct MissilePicker : public sf::Drawable
{
    MissilePicker();
    
    void setPosition(sf::Vector2f pos);
    
    void move(sf::Vector2f offset) {setPosition(getPosition() + offset);}

    void right();
    void left();

    IMissileFactory& getCurrentMissile() {return *factories[currentFactory];}

    sf::Vector2f getPosition() const {return sprites.begin()->getPosition();}
    ~MissilePicker() {delete[] spritesArr;}
private:
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override
    {
        for (auto& i : sprites)
            target.draw(i, states);
        for (auto& i : missiles)
            target.draw(i, states);
    }

    float defaultThickness{1.f};
    float underlinedThickness{2.f};
   
    sf::RectangleShape current;
    sf::RectangleShape* spritesArr{};
    std::span<sf::RectangleShape>sprites;
    sf::Sprite missileTextures[3] {sf::Sprite{util::AssetLoader::get().laser}, sf::Sprite{util::AssetLoader::get().rocket}, sf::Sprite{util::AssetLoader::get().scanner}};
    std::span<sf::Sprite>missiles;

    static constexpr int amount{3};
    int currentFactory{};
    LaserFactory laserFactory;
    RocketFactory rocketFactory;
    ScannerFactory scannerFactory;
    IMissileFactory* factories[amount]{&laserFactory, &rocketFactory, &scannerFactory};
};