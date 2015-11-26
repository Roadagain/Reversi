#ifndef INCLUDE_ROADAGAIN_GAME_HPP
#define INCLUDE_ROADAGAIN_GAME_HPP

#include <utility>

#include "board.hpp"

namespace roadagain
{

class Reversi : public Board
{
public:
    Reversi();
    ~Reversi();

    void start();
    void play();
    void end();

    static const int START_Y = 1;
    static const int START_X = 1;
    static const int END_Y = START_Y + ROW * 2;
    static const int END_X = START_Y + COL * 3;

private:
    bool can_put();
    bool can_put(const std::pair<int, int>& point);
    bool can_put(const std::pair<int, int>& point, int dy, int dx);
    std::pair<int, int> move();
    void put(const std::pair<int, int>& point);
    void reverse(const std::pair<int, int>& point);
    void reverse(const std::pair<int, int>& point, int dy, int dx);
    void change();

    static const int DXY[];

    BoardState now_;
    BoardState next_;
};

}

#endif
