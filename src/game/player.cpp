#include "player.hpp"

Player::Player()
{
    mainTexture.loadFromFile("resources/textures/gameBackground.png");
    sprite.setTexture(mainTexture);
}
