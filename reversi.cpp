#include <ncurses.h>
#include <utility>

#include "board.hpp"
#include "print.hpp"
#include "reversi.hpp"

namespace roadagain
{

Reversi::Reversi() : now_(BLACK), next_(WHITE)
{
}

Reversi::~Reversi()
{
}

void Reversi::start()
{
    print(START_Y, START_X);
}

void Reversi::play()
{
    std::pair<int, int> point;

    for (int i = 0; i < MAX_PUT; i++){
        if (can_put(now_) == false){
            change();
            if (can_put(now_) == false){
                break;
            }
        }
        std::pair<int, int> point = move();
        if (point.first == -1 && point.second == -1){
            break;
        }
        put(point.first, point.second, now_);
        change();
    }
    end();
}

void Reversi::end()
{
    ::move(END_Y + 2, START_X);
    if (black_ == white_){
        printw(" Draw ");
    }
    else {
        printw(" Winner is %s ", black_ > white_ ? "Black" : "White");
    }
}

std::pair<int, int> Reversi::move()
{
    int y = 0;
    int x = 0;
    char c;

    if (matrix_[y][x] == EMPTY){
        print_stone(y, x, now_);
    }
    else {
        print_coordinate(y, x);
    }

    c = getch();
    while (c != '\n' || can_put(y, x, now_) == false){
        if (matrix_[y][x] == EMPTY){
            clear_stone(y, x);
        }
        else {
            clear_coordinate(y, x);
        }
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
          case ' ':
            return (std::pair<int, int>(-1, -1));
        }
        if (matrix_[y][x] == EMPTY){
            print_stone(y, x, now_);
        }
        else {
            print_coordinate(y, x);
        }
        c = getch();
    }
    clear_stone(y, x);

    return (std::pair<int, int>(y, x));
}

void Reversi::change()
{
    now_ = next_;
    next_ = (next_ == BLACK ? WHITE : BLACK);
}

}
