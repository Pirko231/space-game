#pragma once

#include <SFML/Graphics.hpp>

#pragma GCC diagnostic ignored "-Wunused-result"

namespace util
{

struct AssetLoader
{
    static AssetLoader& get()
    {
        static AssetLoader txt_loader;
        return txt_loader;
    }

    sf::Font font;

    sf::Texture background;

    sf::Texture ship1;
    sf::Texture ship2;

    sf::Texture pCrosshair;
    sf::Texture sCrosshair;

    sf::Texture radar;

    sf::Texture turret;

    sf::Texture laser;
    sf::Texture rocket;
    sf::Texture mine;

    sf::Texture asteroids[3];

    sf::Texture shield;

    sf::Texture explosion;
private:
    AssetLoader();
};

};

inline util::AssetLoader::AssetLoader()
{
    background.loadFromFile("resources/textures/gameBackground.png");

    font.openFromFile("resources/fonts/defaultFont.ttf");

    ship1.loadFromFile("resources/textures/Spaceship_tut.png");
    ship2.loadFromFile("resources/textures/Spaceship_tut_thin.png");

    pCrosshair.loadFromFile("resources/textures/crosshair108.png");
    sCrosshair.loadFromFile("resources/textures/crosshair111.png");

    radar.loadFromFile("resources/textures/radar.png");

    laser.loadFromFile("resources/textures/laser.png");
    rocket.loadFromFile("resources/textures/rocket.png");
    mine.loadFromFile("resources/textures/mine.png");

    asteroids[0].loadFromFile("resources/textures/asteroid.png");
    asteroids[1].loadFromFile("resources/textures/asteroid.png");
    asteroids[2].loadFromFile("resources/textures/asteroid.png");

    shield.loadFromFile("resources/textures/shield.png");

    explosion.loadFromFile("resources/textures/explosion.png");
}