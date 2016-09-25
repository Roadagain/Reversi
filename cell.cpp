#include "cell.hpp"

namespace roadagain
{

Cell::Cell() : color(EMPTY)
{
}

Cell::Cell(const Point& point, CellColor color) : point(point), color(color)
{
}

} // namespace roadagain