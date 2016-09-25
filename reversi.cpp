#include <ncurses.h>
#include <utility>

#include "board.hpp"
#include "enemy.hpp"
#include "log.hpp"
#include "print.hpp"
#include "reversi.hpp"

namespace roadagain
{

Reversi::Reversi(CellColor player, Level level) : player_(player), now_(CellColor::BLACK), next_(CellColor::WHITE)
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

    for (int i = 0; i < Board::MAX_PUT; i++){
        if (not board_->can_put(now_)){
            change();
            if (not board_->can_put(now_)){
                break;
            }
        }
        Point p;
        if (now_ == player_){
            p = move();
        }
        else {
            p = enemy_->select(board_, now_);
            getch();
        }
        if (p.y == -1 && p.x == -1){
            break;
        }
        board_->put(p, now_);
        change();
        logs_->push_back(Log(p, now_));
    }
    end();
}

void Reversi::end() const
{
    CellColor winner = board_->winner();
    ::move(Board::END.y + 2, Board::START.x);
    switch (winner){
      case CellColor::BLACK:
        printw(" Winner is Black ");
        break;
      case CellColor::WHITE:
        printw(" Winner is White ");
        break;
      default:
        printw(" Draw ");
        break;
    }
    ::move(Board::END.y + 2, Board::END.x - 6);
    printw(" %02d %02d ", board_->black(), board_->white());
    log_records(*logs_, winner);
}

Point Reversi::move() const
{
    Point p;
    char c;

    if (board_->empty(p)){
        print_stone(p, now_);
    }
    else {
        print_coordinate(p);
    }

    c = getch();
    while (c != '\n' || not board_->can_put(p, now_)){
        if (board_->empty(p)){
            clear_stone(p);
        }
        else {
            clear_coordinate(p);
        }
        switch (c){
          case 'h':
            p.x = (p.x + Board::COL - 1) % Board::COL;
            break;
          case 'j':
            p.y = (p.y + 1) % Board::ROW;
            break;
          case 'k':
            p.y = (p.y + Board::ROW - 1) % Board::ROW;
            break;
          case 'l':
            p.x = (p.x + 1) % Board::COL;
            break;
          case ' ':
            return (Point(-1, -1));
        }
        if (board_->empty(p)){
            print_stone(p, now_);
        }
        else {
            print_coordinate(p);
        }
        c = getch();
    }
    clear_stone(p);

    return (p);
}

void Reversi::change()
{
    now_ = next_;
    next_.reverse();
}

} // namespace roadagain
