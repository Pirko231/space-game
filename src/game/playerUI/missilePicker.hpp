#pragma once
#include <SFML/Graphics.hpp>
#include <span>
#include "missileFactory.hpp"

struct Background : public sf::Drawable
{
    Background(int amount) : spritesArr{new sf::RectangleShape[amount]}, sprites{spritesArr, amount}
    {
        
        for (int i = 0; i < sprites.size(); i++)
        {
            sprites[i].setOutlineThickness(1.f);
            sprites[i].setOutlineColor(sf::Color::White);
            sprites[i].setFillColor(sf::Color{0,0,0,0});
            sprites[i].setSize({10.f,10.f});
        }
    }
    void setPosition(sf::Vector2f pos)
    {
        for (auto& i : sprites)
        {
            i.setPosition(pos);
            pos.x += i.getGlobalBounds().size.x;
        }
    }
    sf::Vector2f getPosition() const {return sprites.begin()->getPosition();}
    ~Background() {delete[] spritesArr;}
private:
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override
    {
        for (auto& i : sprites)
            target.draw(i, states);
    }
   
    sf::RectangleShape* spritesArr{};
    std::span<sf::RectangleShape>sprites;
};

class MissilePicker : public sf::Drawable
{
public:
    MissilePicker();
    void update();
    void setPosition(sf::Vector2f pos) {background.setPosition(pos);}
    void move(sf::Vector2f offset) {background.setPosition(background.getPosition() + offset);}
private:
    static constexpr int amount{3};
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override
    {
        target.draw(background, states);
    }
    Background background;
};