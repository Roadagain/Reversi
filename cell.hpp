#ifndef INCLUDE_ROADAGAIN_CELL
#define INCLUDE_ROADAGAIN_CELL

#include "cellcolor.hpp"
#include "vec2.hpp"

namespace roadagain
{

struct Cell
{
    Vec2 point;
    CellColor color;

    Cell();
    Cell(const Vec2& p, const CellColor& color);
    Cell(int y, int x, const CellColor& color);
    Cell(const CellColor& color);

    void reverse();
    void print(bool coordinate = true) const;
};

} // namespace roadagain

#endif
