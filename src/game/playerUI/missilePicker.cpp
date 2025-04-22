#include "missilePicker.hpp"

MissilePicker::MissilePicker() : background{3}
{
}

void MissilePicker::update()
{
}

void MissilePicker::right()
{
    if (current < amount - 1)
        current++;
    else
        current = 0;
}

void MissilePicker::left()
{
    if (current > 0)
        current--;
    else
        current = amount - 1;
}
