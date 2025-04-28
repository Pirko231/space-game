#pragma once
#include "missile.hpp"

class Rocket : public Missile
{
public:
    Rocket(sf::Vector2f pos, sf::Vector2f moveBy)
    : Missile{util::ConfigLoader::get().rocketLifetime, util::ConfigLoader::get().rocketSpeed, util::ConfigLoader::get().rocketDamage, util::AssetLoader::get().rocket} 
    {
        damage = 50;
        sprite.setScale({0.4f,0.4f});
        launch(pos,moveBy);
    }

    void handleEvents(const Pressed& pressed) const override;
    void update();
    void display();

    float getLifeTime() const {return maxLifeSpan - lifeSpan;}

    sf::Vector2f getMoveBy() const {return moveBy;}
private:
    sf::Angle rotationSpeed{util::ConfigLoader::get().rocketRotationSpeed};
    mutable const Pressed* pressed;
};