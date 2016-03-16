#include <ncurses.h>
#include <cctype>
#include <algorithm>
#include <string>

#include "board.hpp"
#include "color.hpp"
#include "print.hpp"

namespace roadagain
{

BoardState to_state(const char* s)
{
    std::string str(s);

    std::transform(str.begin(), str.end(), str.begin(), toupper);
    if (str == "BLACK"){
        return (BLACK);
    }
    else if (str == "WHITE"){
        return (WHITE);
    }
    else {
        return (EMPTY);
    }
}

Point::Point(int y, int x) : y(y), x(x)
{
}

const int Board::ROW = 8;
const int Board::COL = 8;

const int Board::DEFAULT_STONE = 4;
const int Board::MAX_PUT = ROW * COL - DEFAULT_STONE;

const int Board::START_Y = 1;
const int Board::START_X = 1;
const int Board::END_Y = START_Y + ROW * 2;
const int Board::END_X = START_Y + COL * 3;
const int Board::DXY[] = { -1, 0, 1 };

Board::Board() : black_(DEFAULT_STONE / 2), white_(DEFAULT_STONE / 2)
{
    matrix_ = new BoardState*[ROW]();
    for (int i = 0; i < ROW; i++){
        matrix_[i] = new BoardState[COL]();
    }
    matrix_[ROW / 2 - 1][COL / 2 - 1] = WHITE;
    matrix_[ROW / 2][COL / 2] = WHITE;
    matrix_[ROW / 2 - 1][COL / 2] = BLACK;
    matrix_[ROW / 2][COL / 2 - 1] = BLACK;
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
    Colors::change_color(Colors::BOARD);
    for (int i = 0; i < ROW * 2 + 1; i++){
        for (int j = 0; j < COL * 3 + 1; j++){
            move(START_Y + p.y + i, START_X + p.x + j);
            if (i % 2 == 0){
                addch(j % 3 == 0 ? '+' : '-');
            }
            else {
                if (j % 3 == 0){
                    addch('|');
                }
                else {
                    print_stone(i / 2, j / 3, matrix_[i / 2][j / 3], false);
                }
            }
        }
    }
}

void Board::put(const Point& p, BoardState stone)
{
    matrix_[p.y][p.x] = stone;
    if (stone == BLACK){
        black_++;
    }
    else {
        white_++;
    }
    print_stone(p.y, p.x, stone, false);
    reverse(p, stone);
}

void Board::reverse(const Point& p, BoardState stone)
{
    for (int i = 0; i < 3; i++){
        for (int j = 0; j < 3; j++){
            if (DXY[i] == 0 && DXY[j] == 0){
                continue;
            }
            reverse(p, stone, DXY[i], DXY[j]);
        }
    }
}

void Board::reverse(Point p, BoardState stone, int dy, int dx)
{
    int cnt = 0;

    p.y += dy;
    p.x += dx;
    while (in_board(p) && matrix_[p.y][p.x] != EMPTY && matrix_[p.y][p.x] != stone){
        cnt++;
        p.y += dy;
        p.x += dx;
    }
    if (!in_board(p) || matrix_[p.y][p.x] == EMPTY){
        return;
    }

    while (cnt-- > 0){
        p.y -= dy;
        p.x -= dx;
        matrix_[p.y][p.x] = stone;
        if (stone == BLACK){
            black_++;
            white_--;
        }
        else {
            white_++;
            black_--;
        }
        print_stone(p.y, p.x, stone, false);
    }
}

int Board::reverse_num(const Point& p, BoardState stone) const
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

int Board::reverse_num(Point p, BoardState stone, int dy, int dx) const
{
    int cnt = 0;

    p.y += dy;
    p.x += dx;
    while (in_board(p) && matrix_[p.y][p.x] != EMPTY && matrix_[p.y][p.x] != stone){
        cnt++;
        p.y += dy;
        p.x += dx;
    }
    if (!in_board(p) || matrix_[p.y][p.x] == EMPTY){
        return (0);
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

BoardState Board::winner() const
{
    if (black_ > white_){
        return (BLACK);
    }
    else if (white_ > black_){
        return (WHITE);
    }
    else {
        return (EMPTY);
    }
}

bool Board::in_board(const Point& p) const
{
    return (0 <= p.y && p.y < ROW && 0 <= p.x && p.x < COL);
}

bool Board::empty(const Point& p) const
{
    return (matrix_[p.y][p.x] == EMPTY);
}

bool Board::can_put(BoardState stone) const
{
    for (int i = 0; i < ROW; i++){
        for (int j = 0; j < COL; j++){
            if (can_put(i, j, stone)){
                return (true);
            }
        }
    }
    return (false);
}

bool Board::can_put(int y, int x, BoardState stone) const
{
    if (matrix_[y][x] != EMPTY){
        return (false);
    }
    for (int i = 0; i < 3; i++){
        for (int j = 0; j < 3; j++){
            if (DXY[i] == 0 && DXY[j] == 0){
                continue;
            }
            if (can_put(y, x, stone, DXY[i], DXY[j])){
                return (true);
            }
        }
    }

    return (false);
}

bool Board::can_put(int y, int x, BoardState stone, int dy, int dx) const
{
    bool can_reverse = false;
    y += dy;
    x += dx;
    while (in_board(Point(y, x)) && matrix_[y][x] != EMPTY && matrix_[y][x] != stone){
        can_reverse = true;
        y += dy;
        x += dx;
    }

    return (in_board(Point(y, x)) && can_reverse && matrix_[y][x] == stone);
}

}
