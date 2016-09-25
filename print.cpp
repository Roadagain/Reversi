#include <ncurses.h>

#include "board.hpp"
#include "color.hpp"
#include "colormanager.hpp"
#include "print.hpp"
#include "reversi.hpp"

namespace roadagain
{

void print_stone(const Point& p, CellColor cell, bool coordinate)
{
    char stone;
    switch (cell){
      case EMPTY:
        ColorManager::instance().change_color(ColorManager::BOARD);
        stone = ' ';
        break;
      case BLACK:
        ColorManager::instance().change_color(ColorManager::BLACK);
        stone = 'o';
        break;
      case WHITE:
        ColorManager::instance().change_color(ColorManager::WHITE);
        stone = 'x';
        break;
      default:
        stone = '\0';
        break;
    }
    mvaddch(p.y * 2 + 1 + Board::START.y, p.x * 3 + 1 + Board::START.x, stone);
    addch(stone);
    ColorManager::instance().change_color(ColorManager::BOARD);
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
    ColorManager::instance().change_color(ColorManager::BOARD);
}

} // namespace roadagain
