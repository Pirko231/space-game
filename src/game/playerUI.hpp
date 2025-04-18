#pragma once
#include <SFML/Graphics.hpp>
#include "playerUI/player.hpp"
#include "playerUI/bar.hpp"
#include "assetLoader.hpp"

/// @brief przechowuje interfejs gracza, czyli paski zycia, celownik i radar
class PlayerUI
{
public:
    PlayerUI();

    void handleEvents(const std::optional<sf::Event>& ev);

    void update();

    void display(sf::RenderWindow* window);

    static void init(sf::RenderWindow* _window);

    PlayerUI& setView(const sf::View& _view)
    {
        view = _view;
        return *this;
    }

    PlayerUI& setPlayerPos(sf::Vector2f playerPos)
    {
        player.setPosition(playerPos);
        
        healthBar.setPosition({playerPos.x - view.getSize().x / 4.f, playerPos.y + view.getSize().y / 2.5f});
        energyBar.setPosition({playerPos.x - view.getSize().x / 4.f, playerPos.y + view.getSize().y / 3.2f});

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
        background.setTexture(util::AssetLoader::get().background);
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

    static constexpr float crosshairShipSpeed{0.02f};

    void crosshairHandleEvents(const std::optional<sf::Event>& ev);

    std::pair<sf::Vector2f, sf::Vector2f> moveCross();

    static sf::Sprite background;
};