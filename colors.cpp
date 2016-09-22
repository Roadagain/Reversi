#include <ncurses.h>

#include "color.hpp"
#include "colors.hpp"

namespace roadagain
{

const Color Colors::BOARD = { BOARD_NUMBER, COLOR_BLACK, COLOR_GREEN };
const Color Colors::BLACK = { BLACK_NUMBER, COLOR_BLACK, COLOR_BLACK };
const Color Colors::WHITE = { WHITE_NUMBER, COLOR_WHITE, COLOR_WHITE };

void Colors::init()
{
    if (not has_colors()){
        return;
    }

    start_color();

    register_color(BOARD);
    register_color(BLACK);
    register_color(WHITE);
}

void Colors::register_color(const Color& color)
{
    init_pair(color.number, color.foreground, color.background);
}

void Colors::change_color(const Color& color)
{
    attrset(COLOR_PAIR(color.number));
}

} // namespace roadagain
