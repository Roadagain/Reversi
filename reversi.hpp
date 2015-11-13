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
    std::pair<int, int> move();
    void put(const std::pair<int, int>& point);
    bool reverse(const std::pair<int, int>& point);

private:
    bool reverse(const std::pair<int, int>& point, int dy, int dx);

    int black_;
    int white_;
};

}

#endif