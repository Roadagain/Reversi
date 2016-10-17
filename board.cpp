#include <ncurses.h>
#include <algorithm>

#include "board.hpp"
#include "cell.hpp"
#include "color.hpp"
#include "colormanager.hpp"
#include "print.hpp"
#include "cellcolor.hpp"

namespace roadagain
{

const Point Board::START(1, 1);
const Point Board::END(START.y + ROW * 2, START.x + COL * 3);

const int Board::DXY[] = { -1, 0, 1 };

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

void Board::print(const Point& p) const
{
    ColorManager::instance().change_color(ColorManager::BOARD);
    for (int i = 0; i < ROW * 2 + 1; i++){
        for (int j = 0; j < COL * 3 + 1; j++){
            move(START.y + p.y + i, START.x + p.x + j);
            if (i % 2 == 0){
                addch(j % 3 == 0 ? '+' : '-');
            }
            else {
                if (j % 3 == 0){
                    addch('|');
                }
                else {
                    print_stone(Point(i / 2, j / 3), matrix_[i / 2][j / 3], false);
                }
            }
        }
    }
}

void Board::put(const Cell& cell, bool print_flag)
{
    Point p = cell.point();
    CellColor stone = cell.color();
    matrix_[p.y][p.x] = stone;
    if (print_flag){
        print_stone(p, stone, false);
    }
    reverse(p, stone, print_flag);
    update_counter();
}

void Board::reverse(const Point& p, const CellColor& stone, bool print_flag)
{
    for (int i = 0; i < 3; i++){
        for (int j = 0; j < 3; j++){
            if (DXY[i] == 0 && DXY[j] == 0){
                continue;
            }
            reverse(p, stone, DXY[i], DXY[j], print_flag);
        }
    }
}

void Board::reverse(Point p, const CellColor& stone, int dy, int dx, bool print_flag)
{
    int cnt = 0;

    p.y += dy;
    p.x += dx;
    while (in_board(p) && matrix_[p.y][p.x] != CellColor::EMPTY && matrix_[p.y][p.x] != stone){
        cnt++;
        p.y += dy;
        p.x += dx;
    }
    if (not in_board(p) || matrix_[p.y][p.x] == CellColor::EMPTY){
        return;
    }

    while (cnt-- > 0){
        p.y -= dy;
        p.x -= dx;
        matrix_[p.y][p.x].reverse();
        if (print_flag){
            print_stone(p, stone, false);
        }
    }
}

int Board::reverse_num(const Point& p, const CellColor& stone) const
{
    int cnt = 0;

    for (int i = 0; i < 3; i++){
        for (int j = 0; j < 3; j++){
            if (DXY[i] == 0 && DXY[j] == 0){
                continue;
            }
            cnt += reverse_num(p, stone, DXY[i], DXY[j]);
        }
    }

    return (cnt);
}

int Board::reverse_num(Point p, const CellColor& stone, int dy, int dx) const
{
    int cnt = 0;

    p.y += dy;
    p.x += dx;
    while (in_board(p) && matrix_[p.y][p.x] != CellColor::EMPTY && matrix_[p.y][p.x] != stone){
        cnt++;
        p.y += dy;
        p.x += dx;
    }
    if (not in_board(p) || matrix_[p.y][p.x] == CellColor::EMPTY){
        return (0);
    }

    return (cnt);
}

int Board::count_neighbor(const Point& p, const CellColor& stone)
{
    int cnt = 0;
    for (int i = 0; i < 3; i++){
        for (int j = 0; j < 3; j++){
            if ((DXY[i] == 0 && DXY[j] == 0) || not in_board(Point(p.y + DXY[i], p.x + DXY[j]))){
                continue;
            }
            if (matrix_[p.y + DXY[i]][p.x + DXY[j]] == stone){
                cnt++;
            }
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

bool Board::in_board(const Point& p) const
{
    return (0 <= p.y && p.y < ROW && 0 <= p.x && p.x < COL);
}

bool Board::empty(const Point& p) const
{
    return (matrix_[p.y][p.x] == CellColor::EMPTY);
}

void Board::update_counter()
{
    black_ = white_ = 0;
    for (int i = 0; i < Board::ROW; i++){
        black_ += std::count(matrix_[i], matrix_[i] + Board::COL, CellColor::BLACK);
        white_ += std::count(matrix_[i], matrix_[i] + Board::COL, CellColor::WHITE);
    }
}

bool Board::can_put(const CellColor& stone) const
{
    for (int i = 0; i < ROW; i++){
        for (int j = 0; j < COL; j++){
            if (can_put(Point(i, j), stone)){
                return (true);
            }
        }
    }
    return (false);
}

bool Board::can_put(const Point& p, const CellColor& stone) const
{
    if (matrix_[p.y][p.x] != CellColor::EMPTY){
        return (false);
    }
    for (int i = 0; i < 3; i++){
        for (int j = 0; j < 3; j++){
            if (DXY[i] == 0 && DXY[j] == 0){
                continue;
            }
            if (can_put(p, stone, DXY[i], DXY[j])){
                return (true);
            }
        }
    }

    return (false);
}

bool Board::can_put(Point p, const CellColor& stone, int dy, int dx) const
{
    bool can_reverse = false;
    p.y += dy;
    p.x += dx;
    while (in_board(p) && matrix_[p.y][p.x] != CellColor::EMPTY && matrix_[p.y][p.x] != stone){
        can_reverse = true;
        p.y += dy;
        p.x += dx;
    }

    return (in_board(p) && can_reverse && matrix_[p.y][p.x] == stone);
}

} // namespace roadagain
