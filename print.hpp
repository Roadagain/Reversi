#ifndef INCLUDE_ROADAGAIN_PRINT
#define INCLUDE_ROADAGAIN_PRINT

#include "board.hpp"

namespace roadagain
{

void print_stone(const Cell& cell, bool coordinate = true);
void clear_stone(const Vec2& p);
void print_coordinate(const Vec2& p);
void clear_coordinate(const Vec2& p);
void print_choice(const Cell& cell);

Vec2 convert_to_printable(const Vec2& p);

} // namespace roadagain

#endif
