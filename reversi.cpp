#include <ncurses.h>
#include <utility>

#include "board.hpp"
#include "enemy.hpp"
#include "log.hpp"
#include "print.hpp"
#include "reversi.hpp"

namespace roadagain
{

Reversi::Reversi(const CellColor& player, Level level) : player_(player), now_(CellColor::BLACK), next_(CellColor::WHITE)
{
    board_ = new Board();
    enemy_ = new Enemy(level);
    logs_ = new std::vector<Cell>();
    logs_->reserve(Board::MAX_PUT);
}

Reversi::~Reversi()
{
    delete board_;
    delete enemy_;
    delete logs_;
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
        board_->put(Cell(p, now_));
        change();
        logs_->emplace_back(p, now_);
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
    Cell cell(Point(), now_);
    char c;

    if (board_->empty(cell.point)){
        print_stone(cell);
    }
    else {
        print_coordinate(cell.point);
    }

    c = getch();
    while (c != '\n' || not board_->can_put(cell)){
        if (board_->empty(cell.point)){
            clear_stone(cell.point);
        }
        else {
            clear_coordinate(cell.point);
        }
        switch (c){
          case 'h':
            cell.point.x = (cell.point.x + Board::COL - 1) % Board::COL;
            break;
          case 'j':
            cell.point.y = (cell.point.y + 1) % Board::ROW;
            break;
          case 'k':
            cell.point.y = (cell.point.y + Board::ROW - 1) % Board::ROW;
            break;
          case 'l':
            cell.point.x = (cell.point.x + 1) % Board::COL;
            break;
          case ' ':
            return (Point(-1, -1));
        }
        if (board_->empty(cell.point)){
            print_stone(cell);
        }
        else {
            print_coordinate(cell.point);
        }
        c = getch();
    }
    clear_stone(cell.point);

    return (cell.point);
}

void Reversi::change()
{
    now_ = next_;
    next_.reverse();
}

} // namespace roadagain
