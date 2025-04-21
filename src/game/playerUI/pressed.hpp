#pragma once

struct Pressed
{
    bool w{false},s{false},a{false},d{false};
    bool upCross{false}, downCross{false}, leftCross{false}, rightCross{false};
    bool shoot{false}, shield{false};
    bool space{false}, tab{false}, lShift{false}, rShift{false};
};

struct PlayerKeyBinds
{
    sf::Keyboard::Key up, down, left, right;
    sf::Keyboard::Key crossUp, crossDown, crossLeft, crossRight;
    sf::Keyboard::Key shoot, shield;
};