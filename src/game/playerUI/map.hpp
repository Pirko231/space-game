#pragma once
#include <SFML/Graphics.hpp>
#include "assetLoader.hpp"

class Map : public sf::Drawable
{
public:
    Map(int amount, sf::Vector2f scale = {4.f,4.f})
    {
        sf::Vector2f startPos{};
        for (std::size_t i = 0; i < amount; i++)
        {
            sf::Sprite sprite{util::AssetLoader::get().background};
            sprite.setScale(scale);
            sprite.setPosition(startPos);
            bounds.size.x += sprite.getGlobalBounds().size.x;
            bounds.size.y += sprite.getGlobalBounds().size.y;
            startPos.x += sprite.getGlobalBounds().size.x;
            sprites.push_back(std::move(sprite));
        }
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