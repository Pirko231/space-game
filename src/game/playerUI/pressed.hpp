#pragma once

struct Pressed
{
    bool w{false},s{false},a{false},d{false};
    bool leftCross{false}, rightCross{false};
    bool shoot{false}, shield{false}, scanner{false};
    bool space{false}, tab{false}, lShift{false}, rShift{false};
    bool weaponLeft{false}, weaponRight{false};
};

struct PlayerKeyBinds
{
    sf::Keyboard::Key up, down, left, right;
    sf::Keyboard::Key crossLeft, crossRight;
    sf::Keyboard::Key shoot, shield, scanner;
    sf::Keyboard::Key weaponLeft, weaponRight;
};