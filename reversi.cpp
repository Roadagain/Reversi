#include <ncurses.h>
#include <utility>

#include "board.hpp"
#include "print.hpp"
#include "reversi.hpp"

namespace roadagain
{

Reversi::Reversi() : black_(2), white_(2)
{
}

Reversi::~Reversi()
{
}

void Reversi::start()
{
    print();
}

std::pair<int, int> Reversi::move()
{
    int y = 0;
    int x = 0;
    char c;

    if (matrix_[y][x] == EMPTY){
        print_stone(y, x, BLACK);
    }

    c = getch();
    while (c != '\n'){
        print_stone(y, x, matrix_[y][x]);
        switch (c){
          case 'h':
            x = (x + Board::COL - 1) % Board::COL;
            break;
          case 'j':
            y = (y + 1) % Board::ROW;
            break;
          case 'k':
            y = (y + Board::ROW - 1) % Board::ROW;
            break;
          case 'l':
            x = (x + 1) % Board::COL;
            break;
        }
        if (matrix_[y][x] == EMPTY){
            print_stone(y, x, BLACK);
        }
        c = getch();
    }

    return (std::pair<int, int>(y, x));
}

void Reversi::put(const std::pair<int, int>& point)
{
    int y = point.first;
    int x = point.second;

    matrix_[y][x] = BLACK;
    print_stone(y, x, BLACK);
}

}
