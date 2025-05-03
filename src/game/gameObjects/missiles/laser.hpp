#pragma once
#include "missile.hpp"

class Laser : public Missile
{
public:
    Laser(sf::Vector2f pos, sf::Vector2f dir)
    : Missile{util::ConfigLoader::get().laserLifetime, util::ConfigLoader::get().laserSpeed, util::ConfigLoader::get().laserDamage, util::AssetLoader::get().laser}
    {
        sprite.setScale({0.2f,0.2f});
        temperature = 4000;
        launch(pos,dir);
        sound.setVolume(util::ConfigLoader::get().soundVolume);
        sound.play();
    }

    virtual void update();
    virtual void display();
private:
    static sf::Sound sound;
};