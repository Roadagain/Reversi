#include "board.hpp"
#include "enemy.hpp"

namespace roadagain
{

Enemy::Enemy(Board* board) : board_(board)
{
}

Enemy::~Enemy()
{
    delete board_;
}

}
