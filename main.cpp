#include <ncurses.h>

#include "board.hpp"
#include "color.hpp"
#include "reversi.hpp"
using namespace roadagain;

int main()
{
    initscr();
    cbreak();
    noecho();
    Colors::init();

    Reversi().start();
    getch();

    endwin();
    return (0);
}
