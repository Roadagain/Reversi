#include <ncurses.h>
#include <algorithm>
#include <utility>
#include <vector>

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
        std::vector<Point> choices = board_->can_put(now_);
        if (choices.empty()){
            change();
            choices = board_->can_put(now_);
            if (choices.empty()){
                break;
            }
        }
        for (Point& j : choices){
            print_choice(Cell(j, now_));
        }

        Point p;
        if (now_ == player_){
            p = move(choices);
        }
        else {
            p = enemy_->select(board_, now_);
            if (getch() == 'q'){
                p = Point(-1, -1);
            }
        }
        if (p.y == -1 && p.x == -1){
            break;
        }
        board_->put(Cell(p, now_));
        change();
        logs_->emplace_back(p, now_);

        for (Point& j : choices){
            if (j == p){
                continue;
            }
            clear_stone(j);
        }
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

Point Reversi::move(const std::vector<Point>& choices) const
{
    Cell cell(Point(), now_);
    int c;

    if (board_->empty(cell.point)){
        print_stone(cell);
    }
    else {
        print_coordinate(cell.point);
    }

    c = getch();
    while (c != ' ' || not board_->can_put(cell)){
        if (board_->empty(cell.point)){
            clear_stone(cell.point);
            if (std::find(choices.begin(), choices.end(), cell.point) != choices.end()){
                print_choice(cell);
            }
        }
        else {
            clear_coordinate(cell.point);
        }
        switch (c){
          case 'h':
          case KEY_LEFT:
            cell.point.x = (cell.point.x + Board::COL - 1) % Board::COL;
            break;
          case 'j':
          case KEY_DOWN:
            cell.point.y = (cell.point.y + 1) % Board::ROW;
            break;
          case 'k':
          case KEY_UP:
            cell.point.y = (cell.point.y + Board::ROW - 1) % Board::ROW;
            break;
          case 'l':
          case KEY_RIGHT:
            cell.point.x = (cell.point.x + 1) % Board::COL;
            break;
          case 'q':
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
