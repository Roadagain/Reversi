#include <ncurses.h>

#include "board.hpp"
#include "color.hpp"
#include "print.hpp"
#include "reversi.hpp"

namespace roadagain
{

void print_stone(int y, int x, BoardState state, bool coordinate)
{
    char stone;
    switch (state){
      case EMPTY:
        Colors::change_color(Colors::BOARD);
        stone = ' ';
        break;
      case BLACK:
        Colors::change_color(Colors::BLACK);
        stone = 'o';
        break;
      case WHITE:
        Colors::change_color(Colors::WHITE);
        stone = 'x';
        break;
      default:
        stone = '\0';
        break;
    }
    mvaddch(y * 2 + 1 + Reversi::START_Y, x * 2 + 1 + Reversi::START_X, stone);
    Colors::change_color(Colors::BOARD);
    if (coordinate == true){
        mvaddch(y * 2 + 1 + Reversi::START_Y, 0, '1' + y);
        mvaddch(y * 2 + 1 + Reversi::START_X, Reversi::END_X + 1, '1' + y);
        mvaddch(0, x * 2 + 1 + Reversi::START_X, 'a' + x);
        mvaddch(Reversi::END_Y + 1, x * 2 + 1 + Reversi::START_X, 'a' + x);
    }
    else {
        attron(COLOR_PAIR(0));
        mvaddch(y * 2 + 1 + Reversi::START_Y, 0, ' ');
        mvaddch(y * 2 + 1 + Reversi::START_X, Reversi::END_X + 1, ' ');
        mvaddch(0, x * 2 + 1 + Reversi::START_X, ' ');
        mvaddch(Reversi::END_Y + 1, x * 2 + 1 + Reversi::START_X, ' ');
        Colors::change_color(Colors::BOARD);
    }
}

void clear_stone(int y, int x)
{
    print_stone(y, x, EMPTY, false);
}

}
