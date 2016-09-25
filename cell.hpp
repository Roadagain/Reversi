#ifndef INCLUDE_ROADAGAIN_CELL
#define INCLUDE_ROADAGAIN_CELL

namespace roadagain
{

class Cell
{
public:
    Cell();
    Cell(const Point& p, CellColor color);

private:
    Point point_;
    CellColor color_;
}

} // namespace roadagain