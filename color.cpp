#include <ncurses.h>

#include "color.hpp"

namespace roadagain
{

const int Colors::BOARD_NUMBER = 1;
const int Colors::BLACK_NUMBER = 2;
const int Colors::WHITE_NUMBER = 3;
const Color Colors::BOARD = { BOARD_NUMBER, COLOR_BLACK, COLOR_GREEN };
const Color Colors::BLACK = { BLACK_NUMBER, COLOR_BLACK, COLOR_BLACK };
const Color Colors::WHITE = { WHITE_NUMBER, COLOR_WHITE, COLOR_WHITE };

void Colors::init()
{
    if (has_colors() == false){
        return;
    }

    start_color();

    register_color(BOARD);
}

void Colors::register_color(const Color& color)
{
    init_pair(color.number, color.foreground, color.background);
}

void Colors::change_color(const Color& color)
{
    attrset(COLOR_PAIR(color.number));
}

}
