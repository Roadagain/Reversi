#include <ncurses.h>

#include "color.hpp"

namespace roadagain
{

Color Colors::BOARD = { BOARD_NUM, COLOR_BLACK, COLOR_GREEN };

void Colors::init()
{
    if (has_colors() == false){
        return;
    }

    start_color();
}
}
