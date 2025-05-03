#pragma once
#include "missile.hpp"

class Mine : public Missile
{
public:
    Mine(sf::Vector2f pos, sf::Vector2f moveBy)
    : Missile{util::ConfigLoader::get().mineLifetime, 0.f, util::ConfigLoader::get().mineDamage, util::AssetLoader::get().mine}
    {
        sprite.setScale({0.2f,0.2f});
        temperature = 10;
        launch(pos,moveBy);
        sound.setVolume(util::ConfigLoader::get().soundVolume);
        sound.play();
    }

    virtual void update();
    virtual void display();
private:
    static sf::Sound sound;
};