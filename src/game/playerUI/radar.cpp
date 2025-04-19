#include "radar.hpp"

Radar::Radar() : sprite{util::AssetLoader::get().radar}
{
    sprite.setScale({0.16f,0.16f});
}

void Radar::update()
{
}
