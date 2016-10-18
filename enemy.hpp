#ifndef INCLUDE_ROADAGAIN_ENEMY
#define INCLUDE_ROADAGAIN_ENEMY

#include "board.hpp"
#include "level.hpp"

namespace roadagain
{

class Enemy
{
public:
    Enemy(Level level);
    ~Enemy();

    Point select(const Board* board, const CellColor& stone) const;

    static const int MIN_EVALUTE_VALUE = int(-1e5);
    static const int MAX_DEPTH = 3;
    static const int SCORE_TABLE[Board::ROW][Board::COL];
private:
    Point randomized_select(const Board* board, const CellColor& stone) const;
    Point maximized_select(const Board* board, const CellColor& stone) const;
    Point evaluated_select(const Board* board, const CellColor& stone, int depth = 1) const;
    int reverse_score(Board* board, const Cell& cell, int depth = 1) const;
    int reverse_score(const Board* board, const Cell& cell, const Point& d) const;
    Level level_;
};

} // namespace roadagain

#endif
