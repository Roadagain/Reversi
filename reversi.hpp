#ifndef INCLUDE_ROADAGAIN_GAME_HPP
#define INCLUDE_ROADAGAIN_GAME_HPP

#include <utility>
#include <vector>

#include "board.hpp"
#include "enemy.hpp"
#include "log.hpp"

namespace roadagain
{

class Reversi
{
public:
    Reversi(BoardState player, Level level);
    ~Reversi();

    void start() const;
    void play();
    void end() const;

private:
    std::pair<int, int> move() const;
    void change();

    Board *board_;
    Enemy *enemy_;
    BoardState player_;
    BoardState now_;
    BoardState next_;
    std::vector<Log> *logs_;
};

}

#endif
