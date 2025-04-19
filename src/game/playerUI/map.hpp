#pragma once
#include <SFML/Graphics.hpp>
#include "assetLoader.hpp"

class Map : public sf::Drawable
{
public:
    Map(int rectSize, sf::Vector2f scale = {4.f,4.f})
    {
        sf::Vector2f startPos{};
        sf::Sprite forCopy{util::AssetLoader::get().background};
        forCopy.setScale(scale);
        for (int i = 0; i < rectSize; i++)
        {
            for (int j = 0; j < rectSize; j++)
            {
                sf::Sprite sprite{forCopy};
                sprite.setPosition(startPos);
                startPos.x += forCopy.getGlobalBounds().size.x;
                sprites.push_back(std::move(sprite));
            }
            startPos.y += forCopy.getGlobalBounds().size.y;
        }
        bounds.size.x = forCopy.getGlobalBounds().size.x * rectSize;
        bounds.size.y = forCopy.getGlobalBounds().size.y * rectSize;
    }

    sf::FloatRect getBounds() const {return bounds;}

    sf::Vector2f getRandomPoint() const
    {
        return {static_cast<float>(std::rand() % static_cast<int>(bounds.size.x)), static_cast<float>(std::rand() % static_cast<int>(bounds.size.y))};
    }
private:
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override
    {
        for (auto& i : sprites)
            target.draw(i, states);
    }
    std::vector<sf::Sprite> sprites;
    sf::FloatRect bounds;
};