#pragma once
#include <SFML/Graphics.hpp>
#include "playerUI/player.hpp"

class PlayerUI
{
public:
    PlayerUI() = default;

    PlayerUI& setView(const sf::View& _view)
    {
        view = _view;
        return *this;
    }

    PlayerUI& setPlayerPos(sf::Vector2f pos)
    {
        player.setPosition(pos);
        return *this;
    }

    PlayerUI& setKeyBinds(const PlayerKeyBinds& pKeybinds)
    {
        player.setKeyBinds(pKeybinds);
        return *this;
    }

    PlayerUI& setTextureName(const sf::String& fileName)
    {
        player.setTexture(fileName);
        return *this;
    }

    sf::View& getView() {return view;}
private:
    sf::View view;

    Player player;


};