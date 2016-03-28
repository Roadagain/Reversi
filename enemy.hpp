#ifndef INCLUDE_ROADAGAIN_ENEMY
#define INCLUDE_ROADAGAIN_ENEMY

#include "board.hpp"

namespace roadagain
{

enum Level
{
    EASY,
    MEDIUM,
    HARD
};

class Enemy
{
public:
    Enemy(Level level);
    ~Enemy();

    Point select(const Board* board, BoardState stone) const;
private:
    Point randomized_select(const Board* board, BoardState stone) const;
    Point maximized_select(const Board* board, BoardState stone) const;
    Level level_;
    static const int score[8][8];
};

}

#endif
