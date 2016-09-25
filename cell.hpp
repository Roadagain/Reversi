#ifndef INCLUDE_ROADAGAIN_CELL
#define INCLUDE_ROADAGAIN_CELL

#include "cellcolor.hpp"
#include "point.hpp"

namespace roadagain
{

class Cell
{
public:
    Cell();
    Cell(const Point& p, const CellColor& color);

    void reverse();

private:
    Point point_;
    CellColor color_;
};

} // namespace roadagain

#endif
