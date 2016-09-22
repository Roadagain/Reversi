#include <ncurses.h>

#include "board.hpp"
#include "color.hpp"
#include "print.hpp"
#include "reversi.hpp"

namespace roadagain
{

void print_stone(const Point& p, BoardState state, bool coordinate)
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
    mvaddch(p.y * 2 + 1 + Board::START.y, p.x * 3 + 1 + Board::START.x, stone);
    addch(stone);
    Colors::change_color(Colors::BOARD);
    if (coordinate){
        print_coordinate(p);
    }
    else {
        clear_coordinate(p);
    }
}

void clear_stone(const Point& p)
{
    print_stone(p, EMPTY, false);
}

void print_coordinate(const Point& p)
{
    mvaddch(p.y * 2 + 1 + Board::START.y, 0, '1' + p.y);
    mvaddch(p.y * 2 + 1 + Board::START.x, Board::END.x + 1, '1' + p.y);
    mvaddch(0, p.x * 3 + 1 + Board::START.x, 'a' + p.x);
    mvaddch(Board::END.y + 1, p.x * 3 + 2 + Board::START.x, 'a' + p.x);
}

void clear_coordinate(const Point& p)
{
    attrset(0);
    mvaddch(p.y * 2 + 1 + Board::START.y, 0, ' ');
    mvaddch(p.y * 2 + 1 + Board::START.y, Board::END.x + 1, ' ');
    mvaddch(0, p.x * 3 + 1 + Board::START.x, ' ');
    mvaddch(Board::END.y + 1, p.x * 3 + 2 + Board::START.x, ' ');
    Colors::change_color(Colors::BOARD);
}

}
