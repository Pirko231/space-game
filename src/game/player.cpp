#include "player.hpp"

Player::Player()
{
    mainTexture.loadFromFile("resources/textures/");
    sprite.setTexture(mainTexture);
}
