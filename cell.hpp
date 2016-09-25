#ifndef INCLUDE_ROADAGAIN_CELL
#define INCLUDE_ROADAGAIN_CELL

namespace roadagain
{

enum Cell
{
    EMPTY,
    BLACK,
    WHITE
};

Cell to_cell(const char* s);

Cell reversed(Cell stone);

} // namespace roadagain

#endif
