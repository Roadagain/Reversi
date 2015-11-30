#ifndef INCLUDE_ROADAGAIN_ENEMY
#define INCLUDE_ROADAGAIN_ENEMY

#include <utility>

namespace roadagain
{

class Enemy
{
public:
    Enemy();
    ~Enemy();

    std::pair<int, int> select(const Board* board, BoardState stone) const;
};

}

#endif
