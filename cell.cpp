#include "cell.hpp"

namespace roadagain
{

Cell::Cell()
{
}

Cell::Cell(const Point& point, const CellColor& color) : point_(point), color_(color)
{
}

void Cell::reverse()
{
    color_.reverse();
}

Point Cell::point() const
{
    return (point_);
}

CellColor Cell::color() const
{
    return (color_);
}

} // namespace roadagain
