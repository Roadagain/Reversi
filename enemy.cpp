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

const int Enemy::score_[8][8] = {
    {  30, -10,  10,  10,  10,  10, -10,  30 },
    { -10, -10,  10,  -5,  -5,  10, -10, -10 },
    {  15,  10,   8,   5,   5,   8,  10,  15 },
    {  10,  -5,   5,   0,   0,   5,  -5,  10 },
    {  10,  -5,   5,   0,   0,   5,  -5,  10 },
    {  15,  10,   8,   5,   5,   8,  10,  15 },
    { -10, -10,  10,  -5,  -5,  10, -10, -10 },
    {  30, -10,  15,  10,  10,  15, -10,  30 },
};

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

Point Enemy::evaluated_select(const Board* board, BoardState stone) const
{
    Point p;
    int maximum = -500;

    for (int i = 0; i < Board::ROW; i++){
        for (int j = 0; j < Board::COL; j++){
            if (board->can_put(Point(i, j), stone)){
                int tmp = reverse_score(board, Point(i, j), stone);
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

int Enemy::reverse_score(const Board* board, const Point& p, BoardState stone) const
{
    int score = score[p.y][p.x];
    for (int i = 0; i < 3; i++){
        for (int j = 0; j < 3; j++){
            if (Board::DXY[i] == 0 && Board::DXY[j] == 0){
                continue;
            }
            score += reverse_score(board, p, stone, DXY[i], DXY[j]);
        }
    }

    return (score);
}

int Enemy::reverse_score(const Board* board, const Point& p, BoardState stone, int dy, int dx) const
{
    int score = 0;
    int num = board->reverse_num(p, stone, dy, dx);
    for (int i = 1; i < num; i++){
        score += score[p.y + dy * i][p.x + dx * i];
    }

    return (score);
}

}
