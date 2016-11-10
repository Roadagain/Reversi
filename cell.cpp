#include "cell.hpp"
#include "colormanager.hpp"
#include "print.hpp"

namespace roadagain
{

Cell::Cell()
{
}

Cell::Cell(const Vec2& point, const CellColor& color) : point(point), color(color)
{
}

Cell::Cell(int y, int x, const CellColor& color) : point(y, x), color(color)
{
}

Cell::Cell(const CellColor& color) : color(color)
{
}

void Cell::reverse()
{
    color.reverse();
}

void Cell::print(bool coordinate) const
{
    char stone;
    switch (color){
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

    Vec2 printable = convert_to_printable(point);
    mvputc(printable, stone, true);
    mvputc(printable + Vec2(0, 1), stone, true);
    ColorManager::instance().change_color(ColorManager::BOARD);
    if (coordinate){
        print_coordinate(point);
    }
    else {
        clear_coordinate(point);
    }
}

} // namespace roadagain
