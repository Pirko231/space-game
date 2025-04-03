#include "program.hpp"
#include <cassert>

class Tests
{
public:
    Tests() = delete;
    static void check(Program* _program)
    {
        program = _program;
        assert(keyReaction());
    }

private:
    static Program* program;
    static bool keyReaction()
    {
        sf::Event ev;
        //test 1
        ev.type = sf::Event::KeyPressed;
        ev.key.code = sf::Keyboard::W;
        sf::Vector2f pos {const_cast<Player&>(program->p1UI.getPlayer()).getPosition()};
        const_cast<Player&>(program->p1UI.getPlayer()).handleEvents(ev);
        const_cast<Player&>(program->p1UI.getPlayer()).update();
        if (!(const_cast<Player&>(program->p1UI.getPlayer()).getPosition().y < pos.y))
            return false;

        //test 2
        ev.key.code = sf::Keyboard::S;
        const_cast<Player&>(program->p1UI.getPlayer()).handleEvents(ev);
        const_cast<Player&>(program->p1UI.getPlayer()).update();
        if (!(const_cast<Player&>(program->p1UI.getPlayer()).getPosition().y <= pos.y))
            return false;

        //przywrocenie do stanu poczatkowego
        ev.type = sf::Event::KeyReleased;
        ev.key.code = sf::Keyboard::S;   
        const_cast<Player&>(program->p1UI.getPlayer()).handleEvents(ev);
        ev.key.code = sf::Keyboard::W;   
        const_cast<Player&>(program->p1UI.getPlayer()).handleEvents(ev);

        return true;
    }
};

Program* Tests::program = nullptr;
