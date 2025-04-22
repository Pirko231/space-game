#pragma once
#include <SFML/Graphics.hpp>
#include <span>
#include "assetLoader.hpp"
#include "missileFactory.hpp"
#include "factories/laserFactory.hpp"
#include "factories/rocketFactory.hpp"
#include "factories/scannerFactory.hpp"

struct Background : public sf::Drawable
{
    Background(int amount)
    : spritesArr{new sf::RectangleShape[amount]}, sprites{spritesArr, amount}, missiles{missileTextures}
    {
        
        for (int i = 0; i < sprites.size(); i++)
        {
            sprites[i].setOutlineThickness(1.f);
            sprites[i].setOutlineColor(sf::Color::White);
            sprites[i].setFillColor(sf::Color{0,0,0,0});
            sprites[i].setSize({10.f,10.f});
        }
        for (auto& i : missiles)
            i.setOrigin(i.getGlobalBounds().getCenter());
        missiles[0].setScale({0.2f,0.2f});
        missiles[1].setScale({0.2f,0.2f});
        missiles[2].setScale({0.2f,0.2f});
    }
    void setPosition(sf::Vector2f pos)
    {
        for (auto& i : sprites)
        {
            i.setPosition(pos);
            pos.x += i.getGlobalBounds().size.x;
        }
        //pos.x -= 3 * sprites.begin()->getGlobalBounds().size.x;
        for (std::size_t i = 0; i < missiles.size(); i++)
        {
            missiles[i].setPosition(sprites[i].getGlobalBounds().getCenter());
        }
    }
    sf::Vector2f getPosition() const {return sprites.begin()->getPosition();}
    ~Background() {delete[] spritesArr;}
private:
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override
    {
        for (auto& i : sprites)
            target.draw(i, states);
        for (auto& i : missiles)
            target.draw(i, states);
    }
   
    sf::RectangleShape* spritesArr{};
    std::span<sf::RectangleShape>sprites;
    sf::Sprite missileTextures[3] {sf::Sprite{util::AssetLoader::get().laser}, sf::Sprite{util::AssetLoader::get().rocket}, sf::Sprite{util::AssetLoader::get().scanner}};
    std::span<sf::Sprite>missiles;
};

class MissilePicker : public sf::Drawable
{
public:
    MissilePicker();
    void update();
    void setPosition(sf::Vector2f pos) {background.setPosition(pos);}
    void move(sf::Vector2f offset) {background.setPosition(background.getPosition() + offset);}

    void right();
    void left();

    IMissileFactory& getCurrentMissile() {return *factories[current];}
private:
    static constexpr int amount{3};
    int current{};
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override
    {
        target.draw(background, states);
    }
    Background background;

    LaserFactory laserFactory;
    RocketFactory rocketFactory;
    ScannerFactory scannerFactory;
    IMissileFactory* factories[amount]{&laserFactory, &rocketFactory, &scannerFactory};
};