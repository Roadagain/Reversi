#ifndef INCLUDE_ROADAGAIN_COLOR
#define INCLUDE_ROADAGAIN_COLOR

#include <ncurses.h>

namespace roadagain
{

struct Color
{
    const short number;
    const int foreground;
    const int background;
};

class Colors
{
public:
    static void init();

    static void change_color(const Color& color);

    static const Color BOARD;
    static const Color BLACK;
    static const Color WHITE;

private:
    static void register_color(const Color& color);
    static const int BOARD_NUMBER = 1;
    static const int BLACK_NUMBER = 2;
    static const int WHITE_NUMBER = 3;
};

}

#endif
