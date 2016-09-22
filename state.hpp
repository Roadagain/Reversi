#ifndef INCLUDE_ROADAGAIN_STATE
#define INCLUDE_ROADAGAIN_STATE

namespace roadagain
{

enum BoardState
{
    EMPTY,
    BLACK,
    WHITE
};

BoardState to_state(const char* s);

BoardState reversed(BoardState stone);

} // namespace roadagain

#endif
