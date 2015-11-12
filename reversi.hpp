#ifndef INCLUDE_ROADAGAIN_GAME_HPP
#define INCLUDE_ROADAGAIN_GAME_HPP

#include <utility>

#include "board.hpp"

namespace roadagain
{

class Reversi
{
public:
    Reversi();
    ~Reversi();

    void start();
    std::pair<int, int> put();

private:
    Board *board_;
    int black_;
    int white_;
};

}

#endif
