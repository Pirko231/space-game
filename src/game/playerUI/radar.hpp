#pragma once
#include "managers/collisionManager.hpp"
#include "assetLoader.hpp"
#include "scanner.hpp"

class Radar : private CollisionManager, public sf::Drawable
{
public:
    Radar();

    void setRange(float _range, sf::Vector2f _objectSize)
    {
        range = _range; objectSize = _objectSize; scannerActive = true;
    }
    void setDefault()
    {
        range = defaultRange; objectSize = defaultObjectSize; scannerActive = false;
    }

    void setPosition(sf::Vector2f pos) {sprite.setPosition(pos);}

    void update(const Player* player, sf::Vector2f viewCenter = {});

    void move(sf::Vector2f offset) {sprite.move(offset);}

    sf::FloatRect getGlobalBounds() const {return sprite.getGlobalBounds();}
private:
    void findTargets(sf::Vector2f playerPos);
    void removeTargets(sf::Vector2f playerPos);
    void convertCoordinates(sf::Vector2f playerPos);
    void manageP2(sf::Vector2f playerPos);
    void manageRocket(sf::Vector2f playerPos);

    bool isRepeated(const std::unique_ptr<Asteroid>*);

    void draw(sf::RenderTarget& target, sf::RenderStates states) const override
    {
        target.draw(sprite, states);
        for (auto& i : currentlyDisplayed)
            target.draw(i.first, states);
        if (drawRocket)
            target.draw(rocket, states);
        target.draw(p1, states);
        target.draw(p2,states);
    }
    sf::Sprite sprite;
    float range{util::ConfigLoader::get().range};
    float defaultRange{util::ConfigLoader::get().range};
    sf::Vector2f objectSize{2.f,2.f};
    sf::Vector2f defaultObjectSize{2.f,2.f};
    bool scannerActive{};
    float scale{};
    /// @brief para obiektow
    /// @param sf::RectangleShape - obiekt na radarze
    /// @param std::unique_ptr<Asteroid>* wksaznik do orginalnego obiektu
    std::vector<std::pair<sf::RectangleShape, const std::unique_ptr<Asteroid>*>> currentlyDisplayed;

    sf::RectangleShape p1;
    sf::RectangleShape p2;
    sf::RectangleShape rocket;
    bool drawRocket{};
    const Player* p2Pointer{};
};