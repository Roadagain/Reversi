#include <ncurses.h>

#include "color.hpp"

namespace roadagain
{

const int Colors::BOARD_NUMBER = 1;
const Color Colors::BOARD = { BOARD_NUMBER, COLOR_BLACK, COLOR_GREEN };

void Colors::init()
{
    if (has_colors() == false){
        return;
    }

    start_color();

    register_color(BOARD);
}

void Colors::register_color(Color color)
{
    init_pair(color.number, color.foreground, color.background);
}

}
