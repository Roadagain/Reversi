#include "cell.hpp"

namespace roadagain
{

Cell::Cell() : color(EMPTY)
{
}

Cell::Cell(const Point& point, CellColor color) : point_(point), color_(color)
{
}

void Cell::reverse()
{
    color_ = reversed(color_);
}

} // namespace roadagain