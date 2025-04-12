#pragma once
#include <SFML/Graphics.hpp>
#include "assetLoader.hpp"

class Missile : public sf::Drawable
{
public:
    Missile(float _maxLifeSpan, float _speed) : speed{_speed}, maxLifeSpan{_maxLifeSpan} {}

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
    void launch(sf::Vector2f _pos, sf::Vector2f _dir)
    {
        sprite.setPosition(_pos); dir = _dir;
        moveBy = _dir / 10.f;
    }

    sf::Sprite sprite;
    sf::Vector2f dir;
    sf::Vector2f moveBy;
    float speed;
    const float maxLifeSpan;
    float lifeSpan{0};
};