#include "print_board.hpp"

namespace roadagain
{

Board::Board(int row, int col) : row_(row), col_(col)
{
    matrix_ = new int*[row]();
    for (int i = 0; i < row; i++){
        matrix_[i] = new int[col_]();
    }
}

Board::~Board()
{
    for (int i = 0; i < row_; i++){
        delete[] matrix_[i];
    }
    delete[] matrix_;
}

}
