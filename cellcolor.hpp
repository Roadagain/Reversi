#ifndef INCLUDE_ROADAGAIN_CELL
#define INCLUDE_ROADAGAIN_CELL

namespace roadagain
{

enum CellColor
{
    EMPTY,
    BLACK,
    WHITE
};

CellColor to_cell_color(const char* s);

CellColor reversed(CellColor color);

} // namespace roadagain

#endif
