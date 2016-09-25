#ifndef INCLUDE_ROADAGAIN_CELLCOLOR
#define INCLUDE_ROADAGAIN_CELLCOLOR

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
