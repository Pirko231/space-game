#pragma once
#include "missile.hpp"

class Rocket : public Missile
{
public:
    Rocket(sf::Vector2f pos, sf::Vector2f moveBy)
    : Missile{800.f, 1.f, 50, util::AssetLoader::get().rocket} 
    {
        damage = 50;
        sprite.setScale({0.4f,0.4f});
        launch(pos,moveBy);
    }
    static bool shouldInit() {static bool initted{false}; if (!initted) {initted = true;  return true;} return false;}
    static void init();

    void handleEvents(const std::optional<sf::Event>& ev) override;
    void update();
    void display();
private:
    sf::Angle rotationSpeed{sf::degrees(0.5f)};
};