#ifndef INCLUDE_ROADAGAIN_PRINT_BOARD
#define INCLUDE_ROADAGAIN_PRINT_BOARD

#include <string>

namespace roadagain
{

enum BoardState
{
    EMPTY,
    BLACK,
    WHITE
};

BoardState to_state(const char* s);

struct Point
{
    int y;
    int x;

    Point(int y = 0, int x = 0);
};

class Board
{
public:
    Board();
    ~Board();

    void print(const Point& p = Point(0, 0)) const;

    void put(const Point& p, BoardState stone);
    void reverse(const Point& p, BoardState stone);

    int reverse_num(const Point& p, BoardState stone) const;

    int black() const;
    int white() const;

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
    void reverse(Point p, BoardState stone, int dy, int dx);
    int reverse_num(Point p, BoardState stone, int dy, int dx) const;
    bool can_put(int y, int x, BoardState stone, int dy, int dx) const;

    BoardState** matrix_;
    int black_;
    int white_;
};

}

#endif
