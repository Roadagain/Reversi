#include <ncurses.h>

#include "board.hpp"
using namespace roadagain;

int main()
{
    initscr();
    cbreak();
    noecho();

    Board().print();
    getch();

    endwin();
    return (0);
}
