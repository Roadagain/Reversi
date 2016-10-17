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

    Log(const Point& p, const CellColor& stone);
};

void log_records(const std::vector<Log>& logs, const CellColor& winner);

} // namespace roadagain

#endif
