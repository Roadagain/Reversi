#include "board.hpp"
#include "reversi.hpp"

namespace roadagain
{

Reversi::Reversi() : black_(2), white_(2)
{
    board_ = new Board();
}

Reversi::~Reversi()
{
    delete board_;
}

void Reversi::start()
{
    board_->print();
}

}
