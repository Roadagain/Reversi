#include "game.hpp"

namespace roadagain
{

Reversi::Reversi() : black_(0), white_(0)
{
    board_ = new Board();
}

Reversi::~Reversi()
{
    delete board_;
}

}
