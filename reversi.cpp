#include <ncurses.h>
#include <utility>

#include "board.hpp"
#include "print.hpp"
#include "reversi.hpp"

namespace roadagain
{

Reversi::Reversi() : black_(DEFAULT_STONE / 2), white_(DEFAULT_STONE / 2),
    now_(BLACK), next_(WHITE)
{
}

Reversi::~Reversi()
{
}

void Reversi::start()
{
    print();
}

void Reversi::play()
{
    std::pair<int, int> point;

    for (int i = 0; i < MAX_PUT; i++){
        std::pair<int, int> point = move();
        put(point);
        change();
    }
}

bool Reversi::can_put(const std::pair<int, int>& point)
{
    static const int* dxy = { -1, 0, 1 };
    for (int i = 0; i < 3; i++){
        for (int j = 0; j < 3; j++){
            if (dxy[i] == 0 && dxy[j] == 0){
                continue;
            }
            if (can_put(point, dxy[i], dxy[j]) == true){
                return (true);
            }
        }
    }

    return (false);
}

bool Reversi::can_put(const std::pair<int, int>& point, int dy, int dx)
{
    int y = point.first + dy;
    int x = point.second + dx;

    if (matrix_[y][x] != EMPTY){
        return (false);
    }

    while (in_board(y, x) == true && matrix_[y][x] == next_){
        can_reverse = true;
        y += dy;
        x += dx;
    }

    return (in_board(y, x) == true && can_reverse == true && matrix_[y][x] == now_);
}

std::pair<int, int> Reversi::move()
{
    int y = 0;
    int x = 0;
    char c;

    if (matrix_[y][x] == EMPTY){
        print_stone(y, x, now_);
    }

    c = getch();
    while (c != '\n' || can_put(std::pair<int, int>(y, x)) == false){
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
            print_stone(y, x, now_);
        }
        c = getch();
    }

    return (std::pair<int, int>(y, x));
}

void Reversi::put(const std::pair<int, int>& point)
{
    int y = point.first;
    int x = point.second;

    matrix_[y][x] = now_;
    print_stone(y, x, now_);
    reverse(point);
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

    while (in_board(y, x) == true && matrix_[y][x] == next_){
        cnt++;
        can_reverse = true;
        y += dy;
        x += dx;
    }
    if (in_board(y, x) == false || can_reverse == false || matrix_[y][x] == EMPTY){
        return (false);
    }

    while (cnt-- > 0){
        y -= dy;
        x -= dx;
        matrix_[y][x] = now_;
        print_stone(y, x, now_);
    }
    return (true);
}

void Reversi::change()
{
    now_ = next_;
    next_ = (next_ == BLACK ? WHITE : BLACK);
}

}
