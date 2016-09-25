#ifndef INCLUDE_ROADAGAIN_BOARD
#define INCLUDE_ROADAGAIN_BOARD

#include "point.hpp"
#include "cellcolor.hpp"

namespace roadagain
{

class Board
{
public:
    Board();
    Board(const Board& board);
    ~Board();

    void print(const Point& p = Point(0, 0)) const;

    void put(const Point& p, CellColor stone, bool print_flag = true);
    void reverse(const Point& p, CellColor stone, bool print_flag);

    int reverse_num(const Point& p, CellColor stone) const;
    int reverse_num(Point p, CellColor stone, int dy, int dx) const;
    int count_neighbor(const Point& p, CellColor stone);

    int black() const;
    int white() const;
    void copy_matrix(CellColor** matrix) const;

    CellColor winner() const;

    bool in_board(const Point& p) const;
    bool empty(const Point& p) const;
    bool can_put(CellColor stone) const;
    bool can_put(const Point& p, CellColor stone) const;

    static const int ROW = 8;
    static const int COL = 8;

    static const int DEFAULT_STONE = 4;
    static const int MAX_PUT = ROW * COL - DEFAULT_STONE;

    static const Point START;
    static const Point END;

    static const int DXY[];

private:
    void reverse(Point p, CellColor stone, int dy, int dx, bool print_flag);
    bool can_put(Point p, CellColor stone, int dy, int dx) const;

    CellColor** matrix_;
    int black_;
    int white_;
};

} // namespace roadagain

#endif
