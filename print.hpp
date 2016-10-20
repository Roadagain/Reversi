#ifndef INCLUDE_ROADAGAIN_PRINT
#define INCLUDE_ROADAGAIN_PRINT

#include "board.hpp"

namespace roadagain
{

void print_stone(const Cell& cell, bool coordinate = true);
void clear_stone(const Point& p);
void print_coordinate(const Point& p);
void clear_coordinate(const Point& p);
void print_choice(const Cell& cell);

} // namespace roadagain

#endif
