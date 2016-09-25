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

} // namespace roadagain
