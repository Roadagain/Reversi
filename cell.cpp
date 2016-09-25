#include "cell.hpp"

namespace roadagain
{

Cell::Cell()
{
}

Cell::Cell(const Point& point, CellColor color) : point_(point), color_(color)
{
}

void Cell::reverse()
{
    color_.reverse();
}

} // namespace roadagain
