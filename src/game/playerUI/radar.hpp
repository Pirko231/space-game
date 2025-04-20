#pragma once
#include "managers/collisionManager.hpp"
#include "assetLoader.hpp"

class Radar : private CollisionManager, public sf::Drawable
{
public:
    Radar();

    void setPosition(sf::Vector2f pos) {sprite.setPosition(pos);}

    void update();

    void move(sf::Vector2f offset) {sprite.move(offset);}

    sf::FloatRect getGlobalBounds() const {return sprite.getGlobalBounds();}
private:
    void findTargets(sf::Vector2f playerPos);
    void removeTargets(sf::Vector2f playerPos);

    void draw(sf::RenderTarget& target, sf::RenderStates states) const override
    {
        target.draw(sprite, states);
        for (auto& i : currentlyDisplayed)
            target.draw(i.first, states);
    }
    sf::Sprite sprite;
    float range{100.f};
    /// @brief para obiektow
    /// @param sf::RectangleShape - obiekt na radarze
    /// @param sf::Vector2f pozycja obiektu bez przeskalowania na koordynaty radaru
    std::vector<std::pair<sf::RectangleShape, sf::Vector2f>> currentlyDisplayed;
};