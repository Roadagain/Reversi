#include <ncurses.h>

#include "board.hpp"
#include "color.hpp"
#include "print.hpp"

namespace roadagain
{

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

void Board::print(int y, int x) const
{
    Colors::change_color(Colors::BOARD);
    for (int i = 0; i < ROW * 2 + 1; i++){
        for (int j = 0; j < COL * 3 + 1; j++){
            move(START_Y + y + i, START_X + x + j);
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

void Board::put(int y, int x, BoardState stone)
{
    matrix_[y][x] = stone;
    if (stone == BLACK){
        black_++;
    }
    else {
        white_++;
    }
    print_stone(y, x, stone, false);
    reverse(y, x, stone);
}

void Board::reverse(int y, int x, BoardState stone)
{
    for (int i = 0; i < 3; i++){
        for (int j = 0; j < 3; j++){
            if (DXY[i] == 0 && DXY[j] == 0){
                continue;
            }
            reverse(y, x, stone, DXY[i], DXY[j]);
        }
    }
}

void Board::reverse(int y, int x, BoardState stone, int dy, int dx)
{
    int cnt = 0;

    y += dy;
    x += dx;
    while (in_board(y, x) && matrix_[y][x] != EMPTY && matrix_[y][x] != stone){
        cnt++;
        y += dy;
        x += dx;
    }
    if (!in_board(y, x) || matrix_[y][x] == EMPTY){
        return;
    }

    while (cnt-- > 0){
        y -= dy;
        x -= dx;
        matrix_[y][x] = stone;
        if (stone == BLACK){
            black_++;
            white_--;
        }
        else {
            white_++;
            black_--;
        }
        print_stone(y, x, stone, false);
    }
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

bool Board::in_board(int y, int x) const
{
    return (0 <= y && y < ROW && 0 <= x && x < COL);
}

bool Board::empty(int y, int x) const
{
    return (matrix_[y][x] == EMPTY);
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
    while (in_board(y, x) && matrix_[y][x] != EMPTY && matrix_[y][x] != stone){
        can_reverse = true;
        y += dy;
        x += dx;
    }

    return (in_board(y, x) && can_reverse && matrix_[y][x] == stone);
}

}
