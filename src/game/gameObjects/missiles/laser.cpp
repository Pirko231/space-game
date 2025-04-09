#include "laser.hpp"

sf::Texture Laser::texture{};

void Laser::init()
{
    texture.loadFromFile("resources/textures/missiles/laser.png");
}

void Laser::update()
{
}

void Laser::display()
{
}
