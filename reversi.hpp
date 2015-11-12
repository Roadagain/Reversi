#ifndef INCLUDE_ROADAGAIN_GAME_HPP
#define INCLUDE_ROADAGAIN_GAME_HPP

#include "board.hpp"

namespace roadagain
{

class Reversi
{
public:
    Reversi();
    ~Reversi();

private:
    Board *board_;
    int black_;
    int white_;
};

}

#endif
