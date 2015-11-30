#ifndef INCLUDE_ROADAGAIN_ENEMY
#define INCLUDE_ROADAGAIN_ENEMY

#include <utility>

namespace roadagain
{

class Enemy
{
public:
    Enemy(BoardState stone);
    ~Enemy();

    std::pair<int, int> select(const Board* board) const;

private:
    BoardState stone_;
};

}

#endif
