#include <ncurses.h>

#include "board.hpp"
#include "color.hpp"

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
        move(y + i, x);
        for (int j = 0; j < COL * 2 + 1; j++){
            if (i % 2 == 0){
                addch(j % 2 == 0 ? '+' : '-');
            }
            else {
                if (j % 2 == 0){
                    addch('|');
                }
                else {
                    print_stone(i / 2, j / 2);
                }
            }
        }
    }
}

void Board::print_stone(int y, int x)
{
    char stone = '\0';
    switch (matrix_[y][x]){
      case EMPTY:
        Colors::change_color(Colors::BOARD);
        stone = ' ';
        break;
      case BLACK:
        Colors::change_color(Colors::BLACK);
        stone = 'o';
        break;
      case WHITE:
        Colors::change_color(Colors::WHITE);
        stone = 'x';
        break;
    }
    addch(stone);
    Colors::change_color(Colors::BOARD);
}

void Board::set_stone(int y, int x, BoardState state)
{
    matrix_[y][x] = state;
}

}
