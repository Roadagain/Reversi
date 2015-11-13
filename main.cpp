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

    Reversi reversi;
    reversi.start();
    std::pair<int, int> p = reversi.move();
    reversi.put(p);
    reversi.reverse(p);
    getch();

    endwin();
    return (0);
}
