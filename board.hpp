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
    void reverse(int y, int x, BoardState stone);

    BoardState winner();

    bool in_board(int y, int x);
    bool empty(int y, int x);
    bool can_put(BoardState stone);
    bool can_put(int y, int x, BoardState stone);

    static const int ROW = 8;
    static const int COL = 8;

    static const int DEFAULT_STONE = 4;
    static const int MAX_PUT = ROW * COL - DEFAULT_STONE;

    static const int DXY[];

protected:
    void reverse(int y, int x, BoardState stone, int dy, int dx);
    bool can_put(int y, int x, BoardState stone, int dy, int dx);

    BoardState** matrix_;
    int black_;
    int white_;
};

}

#endif
