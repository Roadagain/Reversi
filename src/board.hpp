#ifndef INCLUDE_ROADAGAIN_PRINT_BOARD
#define INCLUDE_ROADAGAIN_PRINT_BOARD

namespace roadagain
{

class Board
{
public:
    Board();
    ~Board();

    static const int ROW = 8;
    static const int COL = 8;

private:
    int** matrix_;
    const int row_;
    const int col_;
};

}

#endif
