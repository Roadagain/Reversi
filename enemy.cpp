#include <utility>

#include "Scorpio/min-max.hpp"

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
    switch (level_){
        case EASY:
            return (randomized_select(board, stone));
        default:
            return (maximized_select(board, stone));
    }
}

std::pair<int, int> Enemy::randomized_select(const Board* board, BoardState stone) const
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

std::pair<int, int> Enemy::maximized_select(const Board* board, BoardState stone) const
{
    int y = 0;
    int x = 0;
    int maximum = 0;

    for (int i = 0; i < Board::ROW; i++){
        for (int j = 0; j < Board::COL; j++){
            if (board->can_put(y, x, stone)){
                int tmp = board->reverse_num(y, x, stone);
                if (maximum < tmp){
                    maximum = tmp;
                    y = i;
                    x = j;
                }
                else if (maximum == tmp && random() % 2 == 0){
                    y = i;
                    x = j;
                }
            }
        }
    }

    return (std::pair<int, int>(y, x));
}

}
