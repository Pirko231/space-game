#pragma once
#include "missile.hpp"

class Rocket : public Missile
{
public:
    Rocket(sf::Vector2f pos, sf::Vector2f dir) : Missile{50.f, 1.f} {launch(pos,dir); sprite.setTexture(util::AssetLoader::get().rocket);}
    static bool shouldInit() {static bool initted{false}; if (!initted) {initted = true;  return true;} return false;}
    static void init();

    virtual void update();
    virtual void display();
private:

};