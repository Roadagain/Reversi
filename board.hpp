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

BoardState reversed(BoardState stone);

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

    void put(const Point& p, BoardState stone, bool print_flag = true);
    void reverse(const Point& p, BoardState stone, bool print_flag);

    int reverse_num(const Point& p, BoardState stone) const;
    int reverse_num(Point p, BoardState stone, int dy, int dx) const;

    int black() const;
    int white() const;
    void copy_matrix(BoardState** matrix) const;

    BoardState winner() const;

    bool in_board(const Point& p) const;
    bool empty(const Point& p) const;
    bool can_put(BoardState stone) const;
    bool can_put(const Point& p, BoardState stone) const;

    static const int ROW = 8;
    static const int COL = 8;

    static const int DEFAULT_STONE = 4;
    static const int MAX_PUT = ROW * COL - DEFAULT_STONE;

    static const int START_Y = 1;
    static const int START_X = 1;
    static const int END_Y = START_Y + ROW * 2;
    static const int END_X = START_X + COL * 3;

    static const int DXY[];

private:
    void reverse(Point p, BoardState stone, int dy, int dx, bool print_flag);
    bool can_put(Point p, BoardState stone, int dy, int dx) const;

    BoardState** matrix_;
    int black_;
    int white_;
};

}

#endif
