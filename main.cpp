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
        BoardState player = to_state(argv[1]);
        if (player == EMPTY){
            endwin();
            printf("Argument error: %s is not available\n", argv[1]);
            printf("Argument must be BLACK or WHITE\n");
            return (-1);
        }
        reversi = new Reversi(player);
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
