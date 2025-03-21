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
        sf::Vector2f pos {program->player1.getPosition()};
        program->player1.handleEvents(ev);
        program->player1.update();
        if (!(program->player1.getPosition().y < pos.y))
            return false;

        //test 2
        ev.key.code = sf::Keyboard::S;
        program->player1.handleEvents(ev);
        program->player1.update();
        if (!(program->player1.getPosition().y <= pos.y))
            return false;

        //przywrocenie do stanu poczatkowego
        ev.type = sf::Event::KeyReleased;
        ev.key.code = sf::Keyboard::S;   
        program->player1.handleEvents(ev);
        ev.key.code = sf::Keyboard::W;   
        program->player1.handleEvents(ev);

        return true;
    }
};

Program* Tests::program = nullptr;
