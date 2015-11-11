#include <ncurses.h>

#include "color.hpp"

namespace roadagain
{

void Colors::init()
{
    if (has_colors() == false){
        return;
    }

    start_color();
}
}
