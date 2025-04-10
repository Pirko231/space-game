#pragma once
#include <SFML/Graphics.hpp>
#include <memory>
#include "missile.hpp"

class IMissileFactory
{
public:
    /// @brief tworzy obiekt i zwraca go
    /// @param pos pozycja startowa
    /// @param dir pozycja celownika, sluzy do obliczenia poruszania sie obiektu
    /// @return zwraca unique_ptr do klasy dziedziczacej od pocisku @see Missile
    virtual std::unique_ptr<Missile> create(sf::Vector2f pos, sf::Vector2f dir) = 0;

    virtual ~IMissileFactory() = default;
};