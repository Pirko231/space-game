#include "missilePicker.hpp"

MissilePicker::MissilePicker()
    : spritesArr{new sf::RectangleShape[amount]}, sprites{spritesArr, amount}, missiles{missileTextures}
{
    for (std::size_t i = 0; i < sprites.size(); i++)
    {
        sprites[i].setOutlineThickness(defaultThickness);
        sprites[i].setOutlineColor(sf::Color::White);
        sprites[i].setFillColor(sf::Color{0, 0, 0, 0});
        sprites[i].setSize({10.f, 10.f});
    }
    for (auto &i : missiles)
        i.setOrigin(i.getGlobalBounds().getCenter());
    missiles[0].setScale({0.2f, 0.2f});
    missiles[1].setScale({0.2f, 0.2f});
    missiles[2].setScale({0.2f, 0.2f});

    sprites[0].setOutlineThickness(underlinedThickness);

    rocketTimer.setScale({0.2f,0.2f});
    rocketTimer.setOrigin(rocketTimer.getGlobalBounds().getCenter());

    mineTimer.setScale({0.2f,0.2f});
    mineTimer.setOrigin(rocketTimer.getGlobalBounds().getCenter());
}

void MissilePicker::setPosition(sf::Vector2f pos)
{
    for (auto &i : sprites)
    {
        i.setPosition(pos);
        pos.x += i.getGlobalBounds().size.x;
    }
    
    for (std::size_t i = 0; i < missiles.size(); i++)
    {
        missiles[i].setPosition(sprites[i].getGlobalBounds().getCenter());
    }
    rocketTimer.setPosition({sprites[1].getGlobalBounds().getCenter().x - rocketTimer.getGlobalBounds().size.x / 2.f, sprites[1].getGlobalBounds().getCenter().y + rocketTimer.getGlobalBounds().size.y * 1.5f});
    mineTimer.setPosition({sprites[2].getGlobalBounds().getCenter().x - rocketTimer.getGlobalBounds().size.x / 2.f, sprites[2].getGlobalBounds().getCenter().y + rocketTimer.getGlobalBounds().size.y * 1.5f});
}

void MissilePicker::right()
{
    sprites[currentFactory].setOutlineThickness(defaultThickness);
    if (currentFactory < amount - 1)
        currentFactory++;
    else
        currentFactory = 0;
    sprites[currentFactory].setOutlineThickness(underlinedThickness);
}

void MissilePicker::left()
{
    sprites[currentFactory].setOutlineThickness(defaultThickness);
    if (currentFactory > 0)
        currentFactory--;
    else
        currentFactory = amount - 1;
    sprites[currentFactory].setOutlineThickness(underlinedThickness);
}
