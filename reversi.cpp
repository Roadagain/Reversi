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

bool Reversi::reverse(const std::pair<int, int>& point)
{
    bool success = false;

    static const int dxy[] = { -1, 0, 1 };
    for (int i = 0; i < 3; i++){
        for (int j = 0; j < 3; j++){
            if (dxy[i] == 0 && dxy[j] == 0){
                continue;
            }
            bool flag = reverse(point, dxy[i], dxy[j]);
            if (success == false){
                success = flag;
            }
        }
    }

    return (success);
}

bool Reversi::reverse(const std::pair<int, int>& point, int dy, int dx)
{
    int y = point.first + dy;
    int x = point.second + dx;
    int cnt = 0;
    bool can_reverse = false;

    while (in_board(y, x) == true && matrix_[y][x] == WHITE){
        cnt++;
        can_reverse = true;
        y += dy;
        x += dx;
    }
    if (in_board(y, x) == false || can_reverse == false){
        return (false);
    }

    while (cnt-- > 0){
        y -= dy;
        x += dx;
        matrix_[y][x] = BLACK;
        print_stone(y, x, BLACK);
    }
    return (true);
}

}
