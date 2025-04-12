#pragma once
#include <SFML/Graphics.hpp>
#include <cmath>
#include "assetLoader.hpp"

class Missile : public sf::Drawable
{
public:
    /// @brief odbiera eventy i reaguje na nie
    /// @param ev 
    virtual void handleEvents(const sf::Event& ev) {};
    /// @brief aktualizuje swoją pozycję bazujac na wczesniej wyliczonych danych
    virtual void update() = 0;
    /// @brief wyswietla na specjalny ekran dodatkowe rzeczy (zalezy od klasy dziedziczacej)
    virtual void display() {};

    sf::FloatRect getGlobalBounds() const {return sprite.getGlobalBounds();}

    virtual ~Missile() = default;
private:
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override
    {
        target.draw(sprite, states);
    }
protected:
    Missile(float _maxLifeSpan, float _speed, const sf::Texture& _texture)
    : sprite{_texture}, speed{_speed}, maxLifeSpan{_maxLifeSpan}
    {}

    void launch(sf::Vector2f _pos, sf::Vector2f _moveBy)
    {
        sprite.setPosition(_pos);
        sprite.setOrigin(sprite.getGlobalBounds().getCenter());
        moveBy = _moveBy * speed;

        //sprite.setRotation(sf::radians(std::sin(_moveBy.y / _moveBy.length())));
        sprite.setRotation(_moveBy.angle());
    }

    sf::Sprite sprite;
    //sf::Vector2f dir;
    sf::Vector2f moveBy;
    float speed;
    const float maxLifeSpan;
    float lifeSpan{0};
};