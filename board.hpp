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

    void print(int y = 0, int x = 0) const;

    void put(int y, int x, BoardState stone);
    void reverse(int y, int x, BoardState stone);

    BoardState winner() const;

    bool in_board(int y, int x) const;
    bool empty(int y, int x) const;
    bool can_put(BoardState stone) const;
    bool can_put(int y, int x, BoardState stone) const;

    static const int ROW;
    static const int COL;

    static const int DEFAULT_STONE;
    static const int MAX_PUT;

    static const int START_Y;
    static const int START_X;
    static const int END_Y;
    static const int END_X;

    static const int DXY[];

private:
    void reverse(int y, int x, BoardState stone, int dy, int dx);
    bool can_put(int y, int x, BoardState stone, int dy, int dx) const;

    BoardState** matrix_;
    int black_;
    int white_;
};

}

#endif
