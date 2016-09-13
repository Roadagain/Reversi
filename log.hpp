#ifndef INCLUDE_ROADAGAIN_LOG
#define INCLUDE_ROADAGAIN_LOG

#include <vector>

#include "board.hpp"

namespace roadagain
{

struct Log
{
    Point p;
    BoardState stone;

    Log(const Point& p, BoardState stone);
};

void log_records(std::vector<Log>& logs, BoardState winner);

} // namespace roadagain

#endif
