#pragma once
#include <SFML/Graphics.hpp>
#include <cmath>
#include "assetLoader.hpp"
#include "configLoader.hpp"
#include "pressed.hpp"

class Missile : public sf::Drawable
{
public:
    /// @brief odbiera eventy i reaguje na nie
    /// @param ev 
    virtual void handleEvents(const Pressed& pressed) const {};
    /// @brief aktualizuje swoją pozycję bazujac na wczesniej wyliczonych danych
    virtual void update() = 0;
    /// @brief wyswietla na specjalny ekran dodatkowe rzeczy (zalezy od klasy dziedziczacej)
    virtual void display() {};

    int getDamage() {return damage;}

    bool shouldDelete() const {return lifeSpan >= maxLifeSpan;}
    void del() {lifeSpan = maxLifeSpan;}

    sf::FloatRect getGlobalBounds() const {return sprite.getGlobalBounds();}

    virtual ~Missile() = default;
private:
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override
    {
        target.draw(sprite, states);
    }
protected:
    Missile(float _maxLifeSpan, float _speed, int _damage, const sf::Texture& _texture)
    : sprite{_texture}, speed{_speed}, maxLifeSpan{_maxLifeSpan}, damage{_damage}
    {}

    void launch(sf::Vector2f _pos, sf::Vector2f dir)
    {
        sf::Vector2f _moveBy{dir.x - _pos.x, dir.y - _pos.y};
        
        if (_moveBy.x != 0.f || _moveBy.y != 0.f)
        {
            moveBy = _moveBy.normalized() * speed;
            sprite.setOrigin(sprite.getGlobalBounds().getCenter());
            sprite.setRotation(_moveBy.angle());
            sprite.setPosition(_pos);
            lifeSpan++;
        }
        else
            lifeSpan = maxLifeSpan;
    }

    sf::Sprite sprite;
    sf::Vector2f moveBy;
    float speed;
    const float maxLifeSpan;
    float lifeSpan{0};
    int damage{};
};