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

Vec2 Enemy::select(const Board* board, const CellColor& stone) const
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
    {  50, -20,  20,  15,  15,  20, -20,  50 },
    { -20, -20,  20, -10, -10,  20, -20, -20 },
    {  20,  20,  20,   0,   0,  20,  20,  20 },
    {  15, -10,   0,  15,  15,   0, -10,  15 },
    {  15, -10,   0,  15,  15,   0, -10,  15 },
    {  20,  20,  20,   0,   0,  20,  20,  20 },
    { -20, -20,  20, -10, -10,  20, -20, -20 },
    {  50, -20,  20,  15,  15,  20, -20,  50 },
};

Vec2 Enemy::randomized_select(const Board* board, const CellColor& stone) const
{
    int n = random();
    Cell c(stone);

    do {
        c.point.y++;
        if (c.point.y >= Board::ROW){
            c.point.y = 0;
            c.point.x = (c.point.x + 1) % Board::COL;
        }
        while (not board->can_put(c)){
            c.point.y++;
            if (c.point.y >= Board::ROW){
                c.point.y = 0;
                c.point.x = (c.point.x + 1) % Board::COL;
            }
        }
        n--;
    } while (n > 0);

    return (c.point);
}

Vec2 Enemy::maximized_select(const Board* board, const CellColor& stone) const
{
    Vec2 p;
    int maximum = 0;

    for (int i = 0; i < Board::ROW; i++){
        for (int j = 0; j < Board::COL; j++){
            Cell c(i, j, stone);

            if (board->can_put(c)){
                int tmp = board->reverse_num(c);
                if (maximum < tmp){
                    maximum = tmp;
                    p = c.point;
                }
                else if (maximum == tmp && random() % 2 == 0){
                    p = c.point;
                }
            }
        }
    }

    return (p);
}

Vec2 Enemy::evaluated_select(const Board* board, const CellColor& stone, int depth) const
{
    if (depth >= MAX_DEPTH){
        return Vec2(-1, -1);
    }

    Vec2 p;
    int maximum = MIN_EVALUTE_VALUE;

    for (int i = 0; i < Board::ROW; i++){
        for (int j = 0; j < Board::COL; j++){
            Cell c(i, j, stone);

            if (board->can_put(c)){
                Board t_board(*board);
                int tmp = reverse_score(&t_board, c, depth);
                if (maximum < tmp){
                    maximum = tmp;
                    p = c.point;
                }
                else if (maximum == tmp && random() % 2 == 0){
                    p = c.point;
                }
            }
        }
    }

    return (p);
}

int Enemy::reverse_score(Board* board, const Cell& cell, int depth) const
{
    int score = SCORE_TABLE[cell.point.y][cell.point.x] + board->count_neighbor(cell.point, cell.color.reversed()) * 3;
    board->put(cell, false);
    for (const Vec2& d : Board::D){
        score += reverse_score(board, cell, d);
    }
    bool player_put = false;
    for (int i = 0; i < Board::ROW; i++){
        for (int j = 0; j < Board::COL; j++){
            if (board->can_put(Cell(i, j, cell.color.reversed()))){
                score -= 3;
                player_put = true;
            }
        }
    }
    if (not player_put){
        score += 50;
        Vec2 player_point = evaluated_select(board, cell.color, depth + 1);
        if (player_point.y != -1 && player_point.x != -1){
            score += reverse_score(board, Cell(player_point, cell.color), depth + 1);
        }
    }
    else {
        Vec2 player_point = evaluated_select(board, cell.color.reversed(), depth + 1);
        if (player_point.y != -1 && player_point.x != -1){
            score -= reverse_score(board, Cell(player_point, cell.color.reversed()), depth + 1);
        }
    }

    return (score);
}

int Enemy::reverse_score(const Board* board, const Cell& cell, const Vec2& d) const
{
    int score = 0;
    int num = board->reverse_num(cell, d);
    for (int i = 1; i < num; i++){
        score += SCORE_TABLE[cell.point.y + d.y * i][cell.point.x + d.x * i];
    }

    return (score - num * 3);
}

} // namespace roadagain
