#ifndef INCLUDE_ROADAGAIN_REVERSI
#define INCLUDE_ROADAGAIN_REVERSI

#include <vector>

#include "board.hpp"
#include "enemy.hpp"
#include "log.hpp"

namespace roadagain
{

class Reversi
{
public:
    Reversi(const CellColor& player, Level level);
    ~Reversi();

    void start() const;
    void play();
    void end() const;

private:
    Point move(const std::vector<Point>& choices) const;
    void change();

    Board *board_;
    Enemy *enemy_;
    CellColor player_;
    CellColor now_;
    CellColor next_;
    std::vector<Cell> *logs_;
};

} // namespace roadagain

#endif
