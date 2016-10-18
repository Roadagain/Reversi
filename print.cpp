#include <ncurses.h>

#include "board.hpp"
#include "color.hpp"
#include "colormanager.hpp"
#include "print.hpp"
#include "reversi.hpp"

namespace roadagain
{

void print_stone(const Cell& cell, bool coordinate)
{
    char stone;
    switch (cell.color){
      case CellColor::EMPTY:
        ColorManager::instance().change_color(ColorManager::BOARD);
        stone = ' ';
        break;
      case CellColor::BLACK:
        ColorManager::instance().change_color(ColorManager::BLACK);
        stone = 'o';
        break;
      case CellColor::WHITE:
        ColorManager::instance().change_color(ColorManager::WHITE);
        stone = 'x';
        break;
      default:
        stone = '\0';
        break;
    }
    mvaddch(cell.point.y * 2 + 1 + Board::START.y, cell.point.x * 3 + 1 + Board::START.x, stone);
    addch(stone);
    ColorManager::instance().change_color(ColorManager::BOARD);
    if (coordinate){
        print_coordinate(cell.point);
    }
    else {
        clear_coordinate(cell.point);
    }
}

void clear_stone(const Point& p)
{
    print_stone(Cell(p, CellColor::EMPTY), false);
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
