#include "board.hpp"
#include "enemy.hpp"
#include "level.hpp"
#include "random.hpp"

namespace roadagain
{

Enemy::Enemy(Level level) : level_(level)
{
}

Enemy::~Enemy()
{
}

Point Enemy::select(const Board* board, const CellColor& stone) const
{
    switch (level_){
        case EASY:
            return (randomized_select(board, stone));
        case MEDIUM:
            return (maximized_select(board, stone));
        default:
            return (evaluated_select(board, stone));
    }
}

const int Enemy::SCORE_TABLE[Board::ROW][Board::COL] = {
    {  30, -10,  10,  10,  10,  10, -10,  30 },
    { -10, -10,  10,  -5,  -5,  10, -10, -10 },
    {  15,  10,   8,   5,   5,   8,  10,  15 },
    {  10,  -5,   5,   0,   0,   5,  -5,  10 },
    {  10,  -5,   5,   0,   0,   5,  -5,  10 },
    {  15,  10,   8,   5,   5,   8,  10,  15 },
    { -10, -10,  10,  -5,  -5,  10, -10, -10 },
    {  30, -10,  15,  10,  10,  15, -10,  30 },
};

Point Enemy::randomized_select(const Board* board, const CellColor& stone) const
{
    int n = random();
    Point p;

    do {
        p.y++;
        if (p.y >= Board::ROW){
            p.y = 0;
            p.x = (p.x + 1) % Board::COL;
        }
        while (not board->can_put(p, stone)){
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

Point Enemy::maximized_select(const Board* board, const CellColor& stone) const
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

Point Enemy::evaluated_select(const Board* board, const CellColor& stone, int depth) const
{
    if (depth >= MAX_DEPTH){
        return Point(-1, -1);
    }

    Point p;
    int maximum = MIN_EVALUTE_VALUE;

    for (int i = 0; i < Board::ROW; i++){
        for (int j = 0; j < Board::COL; j++){
            if (board->can_put(Point(i, j), stone)){
                Board t_board(*board);
                int tmp = reverse_score(&t_board, Point(i, j), stone, depth);
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

int Enemy::reverse_score(Board* board, const Point& p, const CellColor& stone, int depth) const
{
    int score = SCORE_TABLE[p.y][p.x];
    for (const Point& d : Board::D){
        score += board->count_neighbor(p, stone.reversed());
        score += reverse_score(board, p, stone, d);
        board->put(Cell(p, stone), false);
        bool player_put = false;
        for (int i = 0; i < Board::ROW; i++){
            for (int j = 0; j < Board::COL; j++){
                if (board->can_put(Point(i, j), stone.reversed())){
                    score--;
                    player_put = true;
                }
            }
        }
        if (not player_put){
            score += 30;
            Point player_point = evaluated_select(board, stone, depth + 1);
            if (player_point.y != -1 && player_point.x != -1){
                score += reverse_score(board, player_point, stone, depth + 1);
            }
        }
        else {
            Point player_point = evaluated_select(board, stone.reversed(), depth + 1);
            if (player_point.y != -1 && player_point.x != -1){
                score -= reverse_score(board, player_point, stone.reversed(), depth + 1);
            }
        }
    }

    return (score);
}

int Enemy::reverse_score(const Board* board, const Point& p, const CellColor& stone, const Point& d) const
{
    int score = 0;
    int num = board->reverse_num(p, stone, d);
    for (int i = 1; i < num; i++){
        score += SCORE_TABLE[p.y + d.y * i][p.x + d.x * i];
    }

    return (score);
}

} // namespace roadagain
