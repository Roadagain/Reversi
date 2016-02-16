#ifndef INCLUDE_ROADAGAIN_ENEMY
#define INCLUDE_ROADAGAIN_ENEMY

#include <utility>

#include "board.hpp"

namespace roadagain
{

enum Level
{
    EASY,
    HARD
};

class Enemy
{
public:
    Enemy(Level level);
    ~Enemy();

    std::pair<int, int> select(const Board* board, BoardState stone) const;
private:
    std::pair<int, int> randomized_select(const Board* board, BoardState stone) const;
    Level level_;
};

}

#endif
