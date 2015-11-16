#ifndef INCLUDE_ROADAGAIN_PRINT_BOARD
#define INCLUDE_ROADAGAIN_PRINT_BOARD

namespace roadagain
{

enum BoardState
{
    EMPTY,
    BLACK,
    WHITE
};

class Board
{
public:
    Board();
    ~Board();

    void print(int y = 0, int x = 0);

    bool in_board(int y, int x);

    static const int ROW = 8;
    static const int COL = 8;

protected:
    BoardState** matrix_;
};

}

#endif
