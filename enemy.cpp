#include <utility>

#include "board.hpp"
#include "enemy.hpp"
#include "random.hpp"

namespace roadagain
{

Enemy::Enemy(Level level) : level_(level)
{
}

Enemy::~Enemy()
{
}

std::pair<int, int> Enemy::select(const Board* board, BoardState stone) const
{
    int n = random();
    int y = 0;
    int x = 0;

    do {
        y++;
        if (y >= Board::ROW){
            y = 0;
            x = (x + 1) % Board::COL;
        }
        while (!board->can_put(y, x, stone)){
            y++;
            if (y >= Board::ROW){
                y = 0;
                x = (x + 1) % Board::COL;
            }
        }
        n--;
    } while (n > 0);

    return (std::pair<int, int>(y, x));
}

}
