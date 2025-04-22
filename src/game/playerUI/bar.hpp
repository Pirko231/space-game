#pragma once
#include <SFML/Graphics.hpp>
class Bar : public sf::Drawable
{
public:
    Bar(float*, int min = 0, int max = 100);
    Bar(sf::Vector2f pos, sf::Vector2f size, float *linkedValue, sf::Color outlineColor = sf::Color::Black);

    void setPosition(sf::Vector2f pos);
    sf::Vector2f getPosition() const;
    sf::FloatRect getGlobalBounds() const {return backgroundBar.getGlobalBounds();}
    void move(sf::Vector2f offset);
    void draw(sf::RenderTarget &target, sf::RenderStates states) const;
    bool manageHover(sf::Vector2i mousePos, bool clicked = false);

    // Dodatkowe metody
    void setSize(sf::Vector2f size);
    void setValue(int value);
    int getValue() const;
    void setOutlineColor(sf::Color color);
    void setColor(sf::Color color)
    {
        fillBar.setFillColor(color);
    }

private:
    void updateBar();      // Aktualizuje szerokość i kolor paska
    void updateBarColor(); // Zmienia kolor w zależności od procentu

    sf::RectangleShape backgroundBar;
    sf::RectangleShape fillBar;

    int minValue;     // Domyślnie 0
    int maxValue;     // Domyślnie 100
    float *linkedValue; // Wartość (0-100) przechowywana w zewnętrznej zmiennej
};