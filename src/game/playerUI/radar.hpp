#pragma once
#include "managers/collisionManager.hpp"
#include "assetLoader.hpp"



class Radar : private CollisionManager, public sf::Drawable
{
public:
    Radar();

    void setPosition(sf::Vector2f pos) {sprite.setPosition(pos);}

    void update(const Player* player);

    void move(sf::Vector2f offset) {sprite.move(offset);}

    sf::FloatRect getGlobalBounds() const {return sprite.getGlobalBounds();}
private:
    void findTargets(sf::Vector2f playerPos);
    void removeTargets(sf::Vector2f playerPos);
    void convertCoordinates(sf::Vector2f playerPos);

    bool isRepeated(const std::unique_ptr<Asteroid>*);

    void draw(sf::RenderTarget& target, sf::RenderStates states) const override
    {
        target.draw(sprite, states);
        for (auto& i : currentlyDisplayed)
            target.draw(i.first, states);
        target.draw(p1, states);
    }
    sf::Sprite sprite;
    float range{500.f};
    float scale{};
    /// @brief para obiektow
    /// @param sf::RectangleShape - obiekt na radarze
    /// @param std::unique_ptr<Asteroid>* wksaznik do orginalnego obiektu
    std::vector<std::pair<sf::RectangleShape, const std::unique_ptr<Asteroid>*>> currentlyDisplayed;

    sf::RectangleShape p1;
    sf::RectangleShape p2;
};