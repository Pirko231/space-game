#pragma once
#include "missile.hpp"

class Mine : public Missile
{
public:
    Mine(sf::Vector2f pos, sf::Vector2f moveBy)
    : Missile{1000.f, 0.f, 50, util::AssetLoader::get().mine}
    {
        sprite.setScale({0.2f,0.2f});
        launch(pos,moveBy);
    }
    static bool shouldInit() {static bool initted{false}; if (!initted) {initted = true;  return true;} return false;}
    static void init();

    virtual void update();
    virtual void display();
private:

};