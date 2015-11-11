#include <ncurses.h>

#include "board.hpp"

namespace roadagain
{

Board::Board()
{
    matrix_ = new int*[ROW]();
    for (int i = 0; i < ROW; i++){
        matrix_[i] = new int[COL]();
    }
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
    for (int i = 0; i < ROW * 2 + 1; i++){
        move(y + i, x);
        for (int j = 0; j < COL * 2 + 1; j++){
            if (i % 2 == 0){
                addch(j % 2 == 0 ? '+' : '-');
            }
            else {
                addch(j % 2 == 0 ? '|' : ' ');
            }
        }
    }
}

}
