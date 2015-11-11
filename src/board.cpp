#include "board.hpp"

namespace roadagain
{

Board::Board()
{
    matrix_ = new int*[ROW]();
    for (int i = 0; i < ROW; i++){
        matrix_[i] = new int[COL]();
    }
}

Board::~Board()
{
    for (int i = 0; i < ROW; i++){
        delete[] matrix_[i];
    }
    delete[] matrix_;
}

}
