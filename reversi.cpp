#include <ncurses.h>
#include <utility>

#include "board.hpp"
#include "enemy.hpp"
#include "log.hpp"
#include "print.hpp"
#include "reversi.hpp"

namespace roadagain
{

Reversi::Reversi(BoardState player, Level level) : player_(player), now_(BLACK), next_(WHITE)
{
    board_ = new Board();
    enemy_ = new Enemy(level);
    logs_ = new std::vector<Log>();
    logs_->reserve(Board::MAX_PUT);
}

Reversi::~Reversi()
{
    delete board_;
}

void Reversi::start() const
{
    board_->print();
}

void Reversi::play()
{
    start();

    std::pair<int, int> point;
    for (int i = 0; i < Board::MAX_PUT; i++){
        if (!board_->can_put(now_)){
            change();
            if (!board_->can_put(now_)){
                break;
            }
        }
        std::pair<int, int> point;
        if (now_ == player_){
            point = move();
        }
        else {
            point = enemy_->select(board_, now_);
            getch();
        }
        if (point.first == -1 && point.second == -1){
            break;
        }
        board_->put(point.first, point.second, now_);
        change();
        logs_->push_back(Log(point.first, point.second, now_));
    }
    end();
}

void Reversi::end() const
{
    BoardState winner = board_->winner();
    ::move(Board::END_Y + 2, Board::START_X);
    switch (winner){
      case BLACK:
        printw(" Winner is Black ");
        break;
      case WHITE:
        printw(" Winner is White ");
        break;
      default:
        printw(" Draw ");
        break;
    }
    ::move(Board::END_Y + 2, Board::END_X - 6);
    printw(" %02d %02d ", board_->black(), board_->white());
    log_records(*logs_, winner);
}

std::pair<int, int> Reversi::move() const
{
    int y = 0;
    int x = 0;
    char c;

    if (board_->empty(y, x)){
        print_stone(y, x, now_);
    }
    else {
        print_coordinate(y, x);
    }

    c = getch();
    while (c != '\n' || !board_->can_put(y, x, now_)){
        if (board_->empty(y, x)){
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
        if (board_->empty(y, x)){
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
