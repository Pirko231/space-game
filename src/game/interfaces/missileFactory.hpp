#pragma once
#include <SFML/Graphics.hpp>
#include <memory>
#include "missile.hpp"

class IMissileFactory
{
public:
    /// @brief tworzy obiekt Missile i zwraca go
    /// @param pos pozycja startowa
    /// @param dir pozycja celownika, sluzy do obliczenia poruszania sie obiektu
    /// @return zwraca unique_ptr do klasy dziedziczacej od pocisku @see Missile
    virtual std::unique_ptr<Missile> create(sf::Vector2f pos, sf::Vector2f dir) = 0;

    /// @brief zwraca referencje do samej siebie, aby mozna bylo wyslac obiekt tymczasowy jako argument
    /// @return referencja do siebie
    IMissileFactory& get() {return *this;}

    virtual ~IMissileFactory() = default;
};