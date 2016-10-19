#include "cell.hpp"

namespace roadagain
{

Cell::Cell()
{
}

Cell::Cell(const Point& point, const CellColor& color) : point(point), color(color)
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

} // namespace roadagain
