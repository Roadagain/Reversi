#include <ctime>
#include <cstdlib>
#include <utility>

#include "board.hpp"
#include "enemy.hpp"

namespace roadagain
{

Enemy::Enemy()
{
    std::srand(std::time(NULL));
}

Enemy::~Enemy()
{
}

std::pair<int, int> Enemy::select(Board* board)
{
    int n = std::rand() % Board::ROW * Board::COL;
    int y = 0;
    int x = 0;

    do {
        y++;
        if (y >= Board::ROW){
            y = 0;
            x = (x + 1) % Board::COL;
        }
        while (!board->can_put(y, x, WHITE)){
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
