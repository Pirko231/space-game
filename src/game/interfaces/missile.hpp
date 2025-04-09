#pragma once
#include <SFML/Graphics.hpp>

class Missile : public sf::Drawable
{
public:
    Missile(float _maxLifeSpan, float _speed) : speed{_speed}, maxLifeSpan{_maxLifeSpan} {}
    virtual void handleEvents(const sf::Event& ev) {};
    virtual void update() = 0;
    virtual void display() {};
    virtual ~Missile() = default;
private:
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override
    {
        target.draw(sprite, states);
    }
protected:
    void launch(sf::Vector2f _pos, sf::Vector2f _dir)
    {
        sprite.setPosition(_pos); dir = _dir;
    }

    sf::Sprite sprite;
    sf::Vector2f dir;
    sf::Vector2f moveBy;
    float speed;
    const float maxLifeSpan;
    float lifeSpan{0};
};