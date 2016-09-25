#ifndef INCLUDE_ROADAGAIN_LOG
#define INCLUDE_ROADAGAIN_LOG

#include <vector>

#include "board.hpp"

namespace roadagain
{

struct Log
{
    Point p;
    Cell stone;

    Log(const Point& p, Cell stone);
};

void log_records(std::vector<Log>& logs, Cell winner);

} // namespace roadagain

#endif
