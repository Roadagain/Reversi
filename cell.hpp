#ifndef INCLUDE_ROADAGAIN_CELL
#define INCLUDE_ROADAGAIN_CELL

#include "cellcolor.hpp"
#include "point.hpp"

namespace roadagain
{

struct Cell
{
    Point point;
    CellColor color;

    Cell();
    Cell(const Point& p, const CellColor& color);

    void reverse();
};

} // namespace roadagain

#endif
