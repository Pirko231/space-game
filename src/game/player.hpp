#pragma once

#include <SFML/Graphics.hpp>
#include "pressed.hpp"

#ifdef MEMTRACKER
#include "../perf/memTracker.hpp"
#endif

class Player : public sf::Drawable
{
public:
    Player(const std::string& textureFilename, sf::Keyboard::Key up, sf::Keyboard::Key down, sf::Keyboard::Key left, sf::Keyboard::Key right);

    void handleEvents(const sf::Event&);

    void update();

    sf::Vector2f getCenter() const {return {sprite.getPosition().x + sprite.getLocalBounds().width / 2.f, sprite.getPosition().y + sprite.getLocalBounds().height / 2.f};}

    sf::Vector2f getPosition() const {return sprite.getPosition();}
private:
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override
    {
        target.draw(sprite, states);
    }

    sf::Keyboard::Key up;
    sf::Keyboard::Key down;
    sf::Keyboard::Key left;
    sf::Keyboard::Key right;

    Pressed pressed;

    sf::Vector2f moveBy{0.f,0.f};

    float throttle{0.02f};

    float maxSpeed{8.f};

    sf::Sprite sprite;
    sf::Texture mainTexture;
};