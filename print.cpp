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
    mvaddch(y * 2 + 1 + Board::START_Y, x * 3 + 1 + Board::START_X, stone);
    addch(stone);
    Colors::change_color(Colors::BOARD);
    if (coordinate == true){
        print_coordinate(y, x);
    }
    else {
        clear_coordinate(y, x);
    }
}

void clear_stone(int y, int x)
{
    print_stone(y, x, EMPTY, false);
}

void print_coordinate(int y, int x)
{
    mvaddch(y * 2 + 1 + Board::START_Y, 0, '1' + y);
    mvaddch(y * 2 + 1 + Board::START_X, Board::END_X + 1, '1' + y);
    mvaddch(0, x * 3 + 1 + Board::START_X, 'a' + x);
    mvaddch(Board::END_Y + 1, x * 3 + 2 + Board::START_X, 'a' + x);
}

void clear_coordinate(int y, int x)
{
    attrset(0);
    mvaddch(y * 2 + 1 + Board::START_Y, 0, ' ');
    mvaddch(y * 2 + 1 + Board::START_Y, Board::END_X + 1, ' ');
    mvaddch(0, x * 3 + 1 + Board::START_X, ' ');
    mvaddch(Board::END_Y + 1, x * 3 + 2 + Board::START_X, ' ');
    Colors::change_color(Colors::BOARD);
}

}
