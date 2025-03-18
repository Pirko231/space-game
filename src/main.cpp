#include "program.hpp"

int main()
{
    Program program;
    while (program.running())
    {
        program.handleEvents();
        program.update();
        program.display();
    }
}