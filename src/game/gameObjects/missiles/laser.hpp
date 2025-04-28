#pragma once
#include "missile.hpp"

class Laser : public Missile
{
public:
    Laser(sf::Vector2f pos, sf::Vector2f dir)
    : Missile{600.f, util::ConfigLoader::get().laserSpeed, util::ConfigLoader::get().laserDamage, util::AssetLoader::get().laser}
    {
        sprite.setScale({0.2f,0.2f});

        launch(pos,dir);
    }

    virtual void update();
    virtual void display();
private:
    
};