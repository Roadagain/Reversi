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

    void set_stone(int y, int x, BoardState state);

    BoardState* operator[](int index) const;

    static const int ROW = 8;
    static const int COL = 8;

protected:
    BoardState** matrix_;
};

}

#endif
