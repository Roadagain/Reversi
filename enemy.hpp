#ifndef INCLUDE_ROADAGAIN_ENEMY
#define INCLUDE_ROADAGAIN_ENEMY

namespace roadagain
{

class Enemy
{
public:
    Enemy(Board* board);
    ~Enemy();

private:
    Board* board_;
};

}

#endif
