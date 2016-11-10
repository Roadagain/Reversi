#include <ncurses.h>
#include <algorithm>
#include <vector>

#include "board.hpp"
#include "cell.hpp"
#include "color.hpp"
#include "colormanager.hpp"
#include "print.hpp"
#include "cellcolor.hpp"

namespace roadagain
{

const Vec2 Board::START(1, 1);
const Vec2 Board::END(START.y + COL * 2, START.x + ROW * 3);

const Vec2 Board::D[] = {
    Vec2(-1, -1),
    Vec2(-1,  0),
    Vec2(-1,  1),
    Vec2( 0, -1),
    Vec2( 0,  1),
    Vec2( 1, -1),
    Vec2( 1,  0),
    Vec2( 1,  1),
};

Board::Board() : black_(DEFAULT_STONE / 2), white_(DEFAULT_STONE / 2)
{
    matrix_ = new CellColor*[ROW]();
    for (int i = 0; i < ROW; i++){
        matrix_[i] = new CellColor[COL]();
    }
    matrix_[ROW / 2 - 1][COL / 2 - 1] = CellColor::WHITE;
    matrix_[ROW / 2][COL / 2] = CellColor::WHITE;
    matrix_[ROW / 2 - 1][COL / 2] = CellColor::BLACK;
    matrix_[ROW / 2][COL / 2 - 1] = CellColor::BLACK;
}

Board::Board(const Board& board) : black_(board.black()), white_(board.white())
{
    matrix_ = new CellColor*[ROW]();
    for (int i = 0; i < ROW; i++){
        matrix_[i] = new CellColor[COL]();
    }
    board.copy_matrix(matrix_);
}

Board::~Board()
{
    for (int i = 0; i < ROW; i++){
        delete[] matrix_[i];
    }
    delete[] matrix_;
}

void Board::print() const
{
    ColorManager::instance().change_color(ColorManager::BOARD);
    for (int i = 0; i < ROW * 2 + 1; i++){
        for (int j = 0; j < COL * 3 + 1; j++){
            move(START.y + i, START.x + j);
            if (i % 2 == 0){
                addch(j % 3 == 0 ? '+' : '-');
            }
            else {
                if (j % 3 == 0){
                    addch('|');
                }
                else {
                    print_stone(Cell(i / 2, j / 3, matrix_[i / 2][j / 3]), false);
                }
            }
        }
    }
}

void Board::put(const Cell& cell, bool print_flag)
{
    matrix_[cell.point.y][cell.point.x] = cell.color;
    if (print_flag){
        print_stone(cell, false);
    }
    reverse(cell, print_flag);
    update_counter();
}

void Board::reverse(const Cell& cell, bool print_flag)
{
    for (const Vec2& d : D){
        reverse(cell, d, print_flag);
    }
}

void Board::reverse(const Cell& cell, const Vec2& d, bool print_flag)
{
    int cnt = 0;
    Cell c = cell;

    c.point += d;
    while (in_board(c.point) && cell.color.is_reversed(matrix_[c.point.y][c.point.x])){
        cnt++;
        c.point += d;
    }
    if (not in_board(c.point) || matrix_[c.point.y][c.point.x].empty()){
        return;
    }

    while (cnt-- > 0){
        c.point -= d;
        matrix_[c.point.y][c.point.x].reverse();
        if (print_flag){
            print_stone(c, false);
        }
    }
}

int Board::reverse_num(const Cell& cell) const
{
    int cnt = 0;

    for (const Vec2& d : D){
        cnt += reverse_num(cell, d);
    }

    return (cnt);
}

int Board::reverse_num(const Cell& cell, const Vec2& d) const
{
    int cnt = 0;
    Cell c = cell;

    c.point += d;
    while (in_board(c.point) && cell.color.is_reversed(matrix_[c.point.y][c.point.x])){
        cnt++;
        c.point += d;
    }
    if (not in_board(c.point) || matrix_[c.point.y][c.point.x].empty()){
        return (0);
    }

    return (cnt);
}

int Board::count_neighbor(const Vec2& p, const CellColor& stone)
{
    int cnt = 0;

    for (const Vec2& d : D){
        Vec2 tmp = p + d;
        if (not in_board(tmp)){
            continue;
        }
        if (matrix_[tmp.y][tmp.x] == stone){
            cnt++;
        }
    }

    return (cnt);
}

int Board::black() const
{
    return (black_);
}

int Board::white() const
{
    return (white_);
}

void Board::copy_matrix(CellColor** matrix) const
{
    for (int i = 0; i < COL; i++){
        for (int j = 0; j < ROW; j++){
            matrix[i][j] = matrix_[i][j];
        }
    }
}

CellColor Board::winner() const
{
    if (black_ > white_){
        return (CellColor::BLACK);
    }
    else if (white_ > black_){
        return (CellColor::WHITE);
    }
    else {
        return (CellColor::EMPTY);
    }
}

bool Board::in_board(const Vec2& p) const
{
    return (0 <= p.y && p.y < ROW && 0 <= p.x && p.x < COL);
}

bool Board::empty(const Vec2& p) const
{
    return (matrix_[p.y][p.x].empty());
}

void Board::update_counter()
{
    black_ = white_ = 0;
    for (int i = 0; i < Board::ROW; i++){
        black_ += std::count(matrix_[i], matrix_[i] + Board::COL, CellColor::BLACK);
        white_ += std::count(matrix_[i], matrix_[i] + Board::COL, CellColor::WHITE);
    }
}

std::vector<Vec2> Board::can_put(const CellColor& stone) const
{
    std::vector<Vec2> choices;

    for (int i = 0; i < ROW; i++){
        for (int j = 0; j < COL; j++){
            if (can_put(Cell(i, j, stone))){
                choices.emplace_back(i, j);
            }
        }
    }
    return (choices);
}

bool Board::can_put(const Cell& cell) const
{
    if (not matrix_[cell.point.y][cell.point.x].empty()){
        return (false);
    }
    for (const Vec2& d : D){
        if (can_put(cell, d)){
            return (true);
        }
    }

    return (false);
}

bool Board::can_put(const Cell& cell, const Vec2& d) const
{
    bool can_reverse = false;
    Cell c = cell;

    c.point += d;
    while (in_board(c.point) && cell.color.is_reversed(matrix_[c.point.y][c.point.x])){
        can_reverse = true;
        c.point += d;
    }

    return (in_board(c.point) && can_reverse && matrix_[c.point.y][c.point.x] == cell.color);
}

} // namespace roadagain
