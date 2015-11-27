#ifndef INCLUDE_ROADAGAIN_GAME_HPP
#define INCLUDE_ROADAGAIN_GAME_HPP

#include <utility>

#include "board.hpp"
#include "enemy.hpp"

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

private:
    std::pair<int, int> move();
    void change();

    Board *board_;
    Enemy *enemy_;
    BoardState now_;
    BoardState next_;
};

}

#endif
