#pragma once
#include <SFML/Graphics.hpp>

struct KeyStatus
{
    bool pressed{}, released{};   
};

struct Pressed
{
    void update(const std::optional<sf::Event>& ev)
    {
        for (auto& key : keys)
            key.second.released = false;
        if (const auto* keyP = ev->getIf<sf::Event::KeyPressed>())
            keys[keyP->code].pressed = true;
        if (const auto* keyR = ev->getIf<sf::Event::KeyReleased>())
        {
            keys[keyR->code].pressed = false;
            keys[keyR->code].released = true;
        }
    }

    KeyStatus operator[](sf::Keyboard::Key key) {return keys[key];}

    KeyStatus at(sf::Keyboard::Key key) const {return keys.at(key);}

private:
    std::unordered_map<sf::Keyboard::Key, KeyStatus> keys;
};

struct PlayerKeyBinds
{
    sf::Keyboard::Key up, down, left, right;
    sf::Keyboard::Key crossLeft, crossRight;
    sf::Keyboard::Key shoot, shield, scanner;
    sf::Keyboard::Key weaponLeft, weaponRight;
};