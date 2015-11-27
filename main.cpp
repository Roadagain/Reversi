#include <ncurses.h>

#include "board.hpp"
#include "color.hpp"
#include "reversi.hpp"
using namespace roadagain;

int main(int argc, char** argv)
{
    initscr();
    cbreak();
    noecho();
    curs_set(0);
    Colors::init();

    Reversi *reversi;
    if (argc > 1){
        reversi = new Reversi(to_state(argv[1]));
    }
    else {
        reversi = new Reversi(BLACK);
    }
    reversi->play();
    getch();

    delete reversi;
    endwin();
    return (0);
}
