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

Point Enemy::select(const Board* board, BoardState stone) const
{
    switch (level_){
        case EASY:
            return (randomized_select(board, stone));
        default:
            return (maximized_select(board, stone));
    }
}

Point Enemy::randomized_select(const Board* board, BoardState stone) const
{
    int n = random();
    Point p;

    do {
        p.y++;
        if (p.y >= Board::ROW){
            p.y = 0;
            p.x = (p.x + 1) % Board::COL;
        }
        while (!board->can_put(p, stone)){
            p.y++;
            if (p.y >= Board::ROW){
                p.y = 0;
                p.x = (p.x + 1) % Board::COL;
            }
        }
        n--;
    } while (n > 0);

    return (p);
}

Point Enemy::maximized_select(const Board* board, BoardState stone) const
{
    Point p;
    int maximum = 0;

    for (int i = 0; i < Board::ROW; i++){
        for (int j = 0; j < Board::COL; j++){
            if (board->can_put(Point(i, j), stone)){
                int tmp = board->reverse_num(Point(i, j), stone);
                if (maximum < tmp){
                    maximum = tmp;
                    p.y = i;
                    p.x = j;
                }
                else if (maximum == tmp && random() % 2 == 0){
                    p.y = i;
                    p.x = j;
                }
            }
        }
    }

    return (p);
}

}
