#pragma once
#include <SFML/Graphics.hpp>
#include "playerUI/player.hpp"
#include "assetLoader.hpp"

class PlayerUI
{
public:
    PlayerUI();

    void handleEvents(const sf::Event& ev);

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
        return *this;
    }

    PlayerUI& setKeyBinds(const PlayerKeyBinds& pKeybinds)
    {
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

    static sf::Sprite background;
};