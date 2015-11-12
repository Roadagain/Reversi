#include <ncurses.h>

#include "board.hpp"
#include "color.hpp"
#include "print.hpp"

namespace roadagain
{

void print_stone(int y, int x, BoardState state)
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
    mvaddch(y * 2 + 1, x * 2 + 1, stone);
    Colors::change_color(Colors::BOARD);
}

}
