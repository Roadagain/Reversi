#ifndef INCLUDE_ROADAGAIN_PRINT_BOARD
#define INCLUDE_ROADAGAIN_PRINT_BOARD

namespace roadagain
{

class Board
{
public:
    Board(int row, int col);
    ~Board();

private:
    int** matrix_;
    const int row_;
    const int col_;
};

}

#endif
