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
        if (!scannerActive)
            deleteDatabase();
        range = _range; objectSize = _objectSize; scannerActive = true;
        scale = range / sprite.getGlobalBounds().size.x;
    }
    void setDefault()
    {
        if (scannerActive)
            deleteDatabase();
        range = defaultRange; objectSize = defaultObjectSize; scannerActive = false;
        scale = range / sprite.getGlobalBounds().size.x;
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
        if (drawP2)
            target.draw(p2,states);
    }
    void deleteDatabase()
    {
        currentlyDisplayed.erase(currentlyDisplayed.begin(), currentlyDisplayed.end());
    }

    sf::Sprite sprite;
    float range{util::ConfigLoader::get().range};
    float defaultRange{util::ConfigLoader::get().range};
    sf::Vector2f objectSize{util::ConfigLoader::get().radarObjectSize, util::ConfigLoader::get().radarObjectSize};
    sf::Vector2f defaultObjectSize{util::ConfigLoader::get().radarObjectSize, util::ConfigLoader::get().radarObjectSize};
    bool scannerActive{};
    float scale{};
    /// @brief para obiektow
    /// @param sf::RectangleShape - obiekt na radarze
    /// @param std::unique_ptr<Asteroid>* wksaznik do orginalnego obiektu
    std::vector<std::pair<sf::RectangleShape, const std::unique_ptr<Asteroid>*>> currentlyDisplayed;

    sf::RectangleShape p1;
    bool drawP2{};
    sf::RectangleShape p2;
    sf::RectangleShape rocket;
    bool drawRocket{};
    const Player* p2Pointer{};
};