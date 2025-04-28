#pragma once
#include "missile.hpp"

class Mine : public Missile
{
public:
    Mine(sf::Vector2f pos, sf::Vector2f moveBy)
    : Missile{50.f, 1.f, 0, util::AssetLoader::get().mine}
    {
        launch(pos,moveBy);
    }
    static bool shouldInit() {static bool initted{false}; if (!initted) {initted = true;  return true;} return false;}
    static void init();

    virtual void update();
    virtual void display();
private:

};