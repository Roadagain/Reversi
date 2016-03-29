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

    static const int MAX_DEPTH;
    static const int score_[8][8];
private:
    Point randomized_select(const Board* board, BoardState stone) const;
    Point maximized_select(const Board* board, BoardState stone) const;
    Point evaluated_select(const Board* board, BoardState stone) const;
    int reverse_score(Board* board, const Point& p, BoardState stone, int depth = 1) const;
    int reverse_score(const Board* board, const Point& p, BoardState stone, int dy, int dx) const;
    Level level_;
};

}

#endif
