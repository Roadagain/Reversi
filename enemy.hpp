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

    std::pair<int, int> select(Board* board);
};

}

#endif
