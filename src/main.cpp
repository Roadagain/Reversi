#include <ncurses.h>

#include "board.hpp"
#include "color.hpp"
using namespace roadagain;

int main()
{
    initscr();
    cbreak();
    noecho();
    Colors.init();

    Board().print();
    getch();

    endwin();
    return (0);
}
