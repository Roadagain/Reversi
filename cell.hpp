#ifndef INCLUDE_ROADAGAIN_CELL
#define INCLUDE_ROADAGAIN_CELL

namespace roadagain
{

class Cell
{
public:
    Cell();
    Cell(const Point& p, CellColor color);

    void reverse();

private:
    Point point_;
    CellColor color_;
};

} // namespace roadagain

#endif
