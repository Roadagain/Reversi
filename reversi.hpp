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
    Reversi(Cell player, Level level);
    ~Reversi();

    void start() const;
    void play();
    void end() const;

private:
    Point move() const;
    void change();

    Board *board_;
    Enemy *enemy_;
    Cell player_;
    Cell now_;
    Cell next_;
    std::vector<Log> *logs_;
};

} // namespace roadagain

#endif
