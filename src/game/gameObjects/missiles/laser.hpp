#pragma once
#include "missile.hpp"

class Laser : public Missile
{
public:
    Laser(sf::Vector2f pos, sf::Vector2f dir) : Missile{50.f, 1.f} {launch(pos,dir); sprite.setTexture(texture);}
    static bool shouldInit() {static bool initted{false}; if (!initted) {initted = true;  return true;} return false;}
    static void init();

    virtual void update();
    virtual void display();
private:
    static sf::Texture texture;
};