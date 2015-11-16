#include <ncurses.h>

#include "board.hpp"
#include "color.hpp"
#include "print.hpp"

namespace roadagain
{

Board::Board()
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

void Board::print(int y, int x)
{
    Colors::change_color(Colors::BOARD);
    for (int i = 0; i < ROW * 2 + 1; i++){
        for (int j = 0; j < COL * 2 + 1; j++){
            move(y + i, x + j);
            if (i % 2 == 0){
                addch(j % 2 == 0 ? '+' : '-');
            }
            else {
                if (j % 2 == 0){
                    addch('|');
                }
                else {
                    print_stone(i / 2, j / 2, matrix_[i / 2][j / 2], false);
                }
            }
        }
    }
}

bool Board::in_board(int y, int x)
{
    return (0 <= y && y < ROW && 0 <= x && x < COL);
}

}
