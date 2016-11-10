#include <ncurses.h>

#include "board.hpp"
#include "color.hpp"
#include "colormanager.hpp"
#include "config.hpp"
#include "print.hpp"
#include "reversi.hpp"

namespace roadagain
{

void mvputc(const Vec2& p, char c, bool is_printable)
{
    Vec2 point = p;
    if (not is_printable){
        point = convert_to_printable(p);
    }

    mvaddch(point.y, point.x, c);
}

void clear_stone(const Vec2& p)
{
    Cell(p, CellColor::EMPTY).print(false);
}

void print_coordinate(const Vec2& p)
{
    Vec2 printable = convert_to_printable(p);

    mvputc(Vec2(printable.y, 0), '1' + p.y, true);
    mvputc(Vec2(printable.y, Board::END.x + 1), '1' + p.y, true);
    mvputc(Vec2(0, printable.x), 'a' + p.x, true);
    mvputc(Vec2(Board::END.y + 1, printable.x), 'a' + p.x, true);
}

void clear_coordinate(const Vec2& p)
{
    Vec2 printable = convert_to_printable(p);

    attrset(0);
    mvputc(Vec2(printable.y, 0), ' ', true);
    mvputc(Vec2(printable.y, Board::END.x + 1), ' ', true);
    mvputc(Vec2(0, printable.x), ' ', true);
    mvputc(Vec2(Board::END.y + 1, printable.x), ' ', true);
    ColorManager::instance().change_color(ColorManager::BOARD);
}

void print_choice(const Cell& cell)
{
    if (not Config::instance().choice()){
        return;
    }

    const char choice = '#';

    switch (cell.color){
      case CellColor::BLACK:
        ColorManager::instance().change_color(ColorManager::BLACK_CHOICE);
        break;
      case CellColor::WHITE:
        ColorManager::instance().change_color(ColorManager::WHITE_CHOICE);
        break;
      default:
        return;
    }

    Vec2 printable = convert_to_printable(cell.point);
    mvputc(printable, choice, true);
    mvputc(Vec2(printable.y, printable.x + 1), choice, true);
    ColorManager::instance().change_color(ColorManager::BOARD);
}

Vec2 convert_to_printable(const Vec2& p)
{
    return (Vec2(p.y * 2 + 1 + Board::START.y, p.x * 3 + 1 + Board::START.x));
}

} // namespace roadagain
