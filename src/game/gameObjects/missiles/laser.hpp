#pragma once
#include "missile.hpp"

class Laser : public Missile
{
public:
    Laser(sf::Vector2f pos, sf::Vector2f dir)
    : Missile{600.f, 3.f, util::AssetLoader::get().laser}
    {
        sprite.setScale({0.2f,0.2f});

        launch(pos,dir);
    }
    static bool shouldInit() {static bool initted{false}; if (!initted) {initted = true;  return true;} return false;}
    static void init();

    virtual void update();
    virtual void display();
private:
    
};