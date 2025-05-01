#pragma once
#include <SFML/Graphics.hpp>
#include "playerUI/player.hpp"
#include "playerUI/bar.hpp"
#include "assetLoader.hpp"
#include "map.hpp"
#include "radar.hpp"
#include "shield.hpp"
#include "missilePicker.hpp"

/// @brief przechowuje interfejs gracza, czyli paski zycia, celownik i radar
class PlayerUI
{
public:
    PlayerUI();

    void handleEvents(const std::optional<sf::Event>& ev);

    void update();

    void display(sf::RenderWindow* window);

    PlayerUI& setView(const sf::View& _view)
    {
        view = _view;
        return *this;
    }

    PlayerUI& setPlayerPos(sf::Vector2f playerPos)
    {
        player.setPosition(playerPos);

        missilePicker.setPosition({playerPos.x - view.getSize().x / 6.f, playerPos.y - view.getSize().y / 2.2f});
        
        healthBar.setPosition({playerPos.x - view.getSize().x / 4.f, playerPos.y + view.getSize().y / 2.5f});
        energyBar.setPosition({playerPos.x - view.getSize().x / 4.f, playerPos.y + view.getSize().y / 3.2f});

        radar.setPosition({playerPos.x + view.getSize().x / 5.f, playerPos.y + view.getSize().x / 5.f});

        return *this;
    }

    PlayerUI& setKeyBinds(const PlayerKeyBinds& pKeybinds)
    {
        keyBinds = pKeybinds;
        player.setKeyBinds(pKeybinds);
        return *this;
    }

    PlayerUI& setTexture(const sf::Texture& texture)
    {
        player.setTexture(texture);
        return *this;
    }

    PlayerUI& setMap(Map* map)
    {
        background = map;
        return *this;
    }

    PlayerUI& setSecondPlayer(PlayerUI& pUI) {player2 = &pUI.player; return *this;}

    const Player& getPlayer() const {return player;}
private:
    static sf::RenderWindow* window;

    sf::View view;

    Player player;

    Player* player2{nullptr};

    Bar healthBar;
    Bar energyBar;

    Pressed pressed;

    PlayerKeyBinds keyBinds;

    sf::Sprite crosshairPlayer;
    sf::Sprite crosshairShip;

    sf::Vector2f crosshairPos{};
    float crosshairSpeed{0.5f};
    float crosshairRadius{40.f};

    Radar radar;

    MissilePicker missilePicker;

    static constexpr float crosshairShipSpeed{0.02f};

    void crosshairHandleEvents(const std::optional<sf::Event>& ev);

    std::pair<sf::Vector2f, sf::Vector2f> moveCross();

    void managePlayerCross();

    Map* background;
};