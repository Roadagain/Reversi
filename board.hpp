#ifndef INCLUDE_ROADAGAIN_BOARD
#define INCLUDE_ROADAGAIN_BOARD

#include <vector>

#include "vec2.hpp"
#include "cell.hpp"
#include "cellcolor.hpp"

namespace roadagain
{

class Board
{
public:
    Board();
    Board(const Board& board);
    ~Board();

    void print(const Vec2& p = Vec2(0, 0)) const;

    void put(const Cell& cell, bool print_flag = true);

    int reverse_num(const Cell& cell) const;
    int reverse_num(const Cell& cell, const Vec2& d) const;
    int count_neighbor(const Vec2& p, const CellColor& stone);

    int black() const;
    int white() const;
    void copy_matrix(CellColor** matrix) const;

    CellColor winner() const;

    bool in_board(const Vec2& p) const;
    bool empty(const Vec2& p) const;
    std::vector<Vec2> can_put(const CellColor& stone) const;
    bool can_put(const Cell& cell) const;

    static const int ROW = 8;
    static const int COL = 8;

    static const int DEFAULT_STONE = 4;
    static const int MAX_PUT = ROW * COL - DEFAULT_STONE;

    static const Vec2 START;
    static const Vec2 END;

    static const int NEIGHBOR = 8;
    static const Vec2 D[NEIGHBOR];

private:
    void update_counter();
    void reverse(const Cell& cell, bool print_flag);
    void reverse(const Cell& stone, const Vec2& d, bool print_flag);
    bool can_put(const Cell& stone, const Vec2& d) const;

    CellColor** matrix_;
    int black_;
    int white_;
};

} // namespace roadagain

#endif
