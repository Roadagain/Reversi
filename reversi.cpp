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
    print(START_Y, START_X);
}

void Reversi::play()
{
    std::pair<int, int> point;

    for (int i = 0; i < MAX_PUT; i++){
        if (can_put() == false){
            change();
            if (can_put() == false){
                break;
            }
        }
        std::pair<int, int> point = move();
        put(point);
        change();
    }
    end();
}

void Reversi::end()
{
    ::move(ROW * 2 + 3, 0);
    if (black_ == white_){
        printw("Draw");
    }
    else {
        printw("Winner is %s", black_ > white_ ? "White" : "Black");
    }
}

const int Reversi::DXY[] = { -1, 0, 1 };

bool Reversi::can_put()
{
    for (int i = 0; i < ROW; i++){
        for (int j = 0; j < COL; j++){
            if (can_put(std::pair<int, int>(i, j)) == true){
                return (true);
            }
        }
    }
    return (false);
}

bool Reversi::can_put(const std::pair<int, int>& point)
{
    if (matrix_[point.first][point.second] != EMPTY){
        return (false);
    }
    for (int i = 0; i < 3; i++){
        for (int j = 0; j < 3; j++){
            if (DXY[i] == 0 && DXY[j] == 0){
                continue;
            }
            if (can_put(point, DXY[i], DXY[j]) == true){
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

    bool can_reverse = false;
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
    else {
        print_coordinate(y, x);
    }

    c = getch();
    while (c != '\n' || can_put(std::pair<int, int>(y, x)) == false){
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

void Reversi::put(const std::pair<int, int>& point)
{
    int y = point.first;
    int x = point.second;

    matrix_[y][x] = now_;
    if (now_ == BLACK){
        black_++;
    }
    else {
        white_++;
    }
    print_stone(y, x, now_, false);
    reverse(point);
}

void Reversi::reverse(const std::pair<int, int>& point)
{
    for (int i = 0; i < 3; i++){
        for (int j = 0; j < 3; j++){
            if (DXY[i] == 0 && DXY[j] == 0){
                continue;
            }
            reverse(point, DXY[i], DXY[j]);
        }
    }
}

void Reversi::reverse(const std::pair<int, int>& point, int dy, int dx)
{
    int y = point.first + dy;
    int x = point.second + dx;
    int cnt = 0;

    while (in_board(y, x) == true && matrix_[y][x] == next_){
        cnt++;
        y += dy;
        x += dx;
    }
    if (in_board(y, x) == false || matrix_[y][x] == EMPTY){
        return;
    }

    while (cnt-- > 0){
        y -= dy;
        x -= dx;
        matrix_[y][x] = now_;
        if (now_ == BLACK){
            black_++;
            white_--;
        }
        else {
            white_++;
            black_--;
        }
        print_stone(y, x, now_, false);
    }
}

void Reversi::change()
{
    now_ = next_;
    next_ = (next_ == BLACK ? WHITE : BLACK);
}

}
