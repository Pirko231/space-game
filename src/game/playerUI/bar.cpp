#include "bar.hpp"
#include <algorithm>

Bar::Bar(int* linkedValue) : minValue{0}, maxValue{100}, linkedValue{linkedValue}
{
    backgroundBar.setPosition({0.f,0.f});
    backgroundBar.setSize({60.f,10.f});
    backgroundBar.setFillColor(sf::Color::Transparent);
    backgroundBar.setOutlineColor(sf::Color::Black);
    backgroundBar.setOutlineThickness(1.f);

    fillBar.setPosition({0.f,0.f});
    fillBar.setSize({0.f, 15.f});
    fillBar.setFillColor(sf::Color::Red);

    updateBar();
}

Bar::Bar(sf::Vector2f pos, sf::Vector2f size, int *linkedValue, sf::Color outlineColor)
    : Bar{linkedValue}
{
    backgroundBar.setPosition(pos);
    backgroundBar.setSize(size);
    backgroundBar.setFillColor(sf::Color::Transparent);
    backgroundBar.setOutlineColor(outlineColor);
    backgroundBar.setOutlineThickness(1.f);

    fillBar.setPosition(pos);
    fillBar.setSize({0.f, size.y}); // startowo 0 szerokości
    //fillBar.setFillColor(sf::Color::Red);

    
}

void Bar::setPosition(sf::Vector2f pos)
{
    backgroundBar.setPosition(pos);
    fillBar.setPosition(pos);
    updateBar();
}

sf::Vector2f Bar::getPosition() const
{
    return backgroundBar.getPosition();
}

void Bar::move(sf::Vector2f offset)
{
    backgroundBar.move(offset);
    fillBar.move(offset);
}

void Bar::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(backgroundBar, states);
    target.draw(fillBar, states);
}

bool Bar::manageHover(sf::Vector2i /*mousePos*/, bool /*clicked*/)
{
    // Bar nie reaguje na interakcje, zwracamy false
    return false;
}

void Bar::setSize(sf::Vector2f size)
{
    backgroundBar.setSize(size);
    updateBar();
}

void Bar::setValue(int value)
{
    if (linkedValue)
    {
        // Ograniczamy do zakresu [minValue, maxValue]
        *linkedValue = std::clamp(value, minValue, maxValue);
        updateBar();
    }
}

int Bar::getValue() const
{
    return (linkedValue) ? *linkedValue : 0;
}

void Bar::setOutlineColor(sf::Color color)
{
    backgroundBar.setOutlineColor(color);
}

void Bar::updateBar()
{
    if (!linkedValue) return;
    float range = static_cast<float>(maxValue - minValue);
    float pct   = (*linkedValue - minValue) / range; 
    pct         = std::max(0.f, std::min(1.f, pct)); 

    // Ustaw szerokość wypełnienia
    sf::Vector2f size = backgroundBar.getSize();
    fillBar.setSize({ size.x * pct, size.y });

    updateBarColor();
}

void Bar::updateBarColor()
{
    /*if (!linkedValue) return;
    float pct = 100.f * (*linkedValue - minValue) / (maxValue - minValue);

    if (pct < 30.f)
        fillBar.setFillColor(sf::Color::Red);
    else if (pct < 60.f)
        fillBar.setFillColor(sf::Color::Yellow);
    else if (pct < 90.f)
        fillBar.setFillColor(sf::Color::Green);
    else
        fillBar.setFillColor(sf::Color::Blue);*/
}