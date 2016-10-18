#include "cell.hpp"

namespace roadagain
{

Cell::Cell()
{
}

Cell::Cell(const Point& point, const CellColor& color) : point(point), color(color)
{
}

void Cell::reverse()
{
    color.reverse();
}

} // namespace roadagain
