#ifndef INCLUDE_ROADAGAIN_PRINT
#define INCLUDE_ROADAGAIN_PRINT

#include "board.hpp"

namespace roadagain
{

void print_stone(int y, int x, BoardState state, bool coordinate = true);
void clear_stone(int y, int x);

}

#endif
