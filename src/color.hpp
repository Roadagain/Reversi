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

    static const Color BOARD;

private:
    static const int BOARD_NUMBER;
};

}

#endif
