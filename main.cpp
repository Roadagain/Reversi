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
    curs_set(0);
    Colors::init();

    Reversi reversi;
    reversi.play();
    getch();

    endwin();
    return (0);
}
