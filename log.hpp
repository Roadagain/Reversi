#ifndef INCLUDE_ROADAGAIN_LOG
#define INCLUDE_ROADAGAIN_LOG

#include <vector>

#include "board.hpp"

namespace roadagain
{

struct Log
{
    Point p;
    CellColor stone;

    Log(const Point& p, CellColor stone);
};

void log_records(std::vector<Log>& logs, CellColor winner);

} // namespace roadagain

#endif
