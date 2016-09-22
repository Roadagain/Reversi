#include <ncurses.h>

#include "color.hpp"
#include "colormanager.hpp"

namespace roadagain
{

const Color ColorManager::BOARD = { BOARD_NUMBER, COLOR_BLACK, COLOR_GREEN };
const Color ColorManager::BLACK = { BLACK_NUMBER, COLOR_BLACK, COLOR_BLACK };
const Color ColorManager::WHITE = { WHITE_NUMBER, COLOR_WHITE, COLOR_WHITE };

void ColorManager::init()
{
    if (not has_colors()){
        return;
    }

    start_color();

    register_color(BOARD);
    register_color(BLACK);
    register_color(WHITE);
}

void ColorManager::register_color(const Color& color)
{
    init_pair(color.number, color.foreground, color.background);
}

void ColorManager::change_color(const Color& color)
{
    attrset(COLOR_PAIR(color.number));
}

} // namespace roadagain
