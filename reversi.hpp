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
    void play();
    void end();

    static const int START_Y = 1;
    static const int START_X = 1;
    static const int END_Y = START_Y + Board::ROW * 2;
    static const int END_X = START_Y + Board::COL * 3;

private:
    std::pair<int, int> move();
    void change();

    Board *board_;
    BoardState now_;
    BoardState next_;
};

}

#endif
