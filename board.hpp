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

    void put(int y, int x, BoardState stone);

    bool in_board(int y, int x);

    static const int ROW = 8;
    static const int COL = 8;

    static const int DEFAULT_STONE = 4;
    static const int MAX_PUT = ROW * COL - DEFAULT_STONE;

protected:
    BoardState** matrix_;
    int black_;
    int white_;
};

}

#endif
