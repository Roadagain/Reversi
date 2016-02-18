#ifndef INCLUDE_ROADAGAIN_LOG
#define INCLUDE_ROADAGAIN_LOG

#include <vector>

#include "board.hpp"

namespace roadagain
{

struct Log
{
    int y;
    int x;
    BoardState stone;
};

void log_records(std::vector<Log> logs);

}

#endif
