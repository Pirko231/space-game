#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "assetLoader.hpp"
#include "configLoader.hpp"

class Explosion : public sf::Drawable
{
public:
    Explosion(const sf::SoundBuffer& _sound, sf::Vector2f pos = {}, sf::Vector2f scale = {1.f,1.f}, int _animationSpeed = 5)
    : sound{_sound}, animationSpeed{_animationSpeed}
    {
        sprite.setTextureRect(sf::IntRect{sf::Vector2i{0,0}, sf::Vector2i{128,128}});
        sprite.setOrigin(sprite.getLocalBounds().getCenter());
        sprite.setScale(scale);
        sprite.setPosition(pos);

        sound.setVolume(util::ConfigLoader::get().soundVolume * 6.f);
    }
    void setPosition(sf::Vector2f pos) {sprite.setPosition(pos);}
    void playSound() {sound.play();}
    void update()
    {
        if (frames >= animationSpeed)
            frames = 0;
        else
        {
            frames++;
            return;
        }
        if (currentFrame < 17)
        {
            sf::IntRect pos{sprite.getTextureRect()};
            pos.position.x += pos.size.x;
            sprite.setTextureRect(pos);
            currentFrame++;
        }
    }
    bool animationFinished() const {return currentFrame >= 17;}

private:
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override
    {
        target.draw(sprite, states);
    }
    sf::Sprite sprite{util::AssetLoader::get().explosion};
    sf::Sound sound;
    int frames{};
    int currentFrame{};
    int animationSpeed{};
};