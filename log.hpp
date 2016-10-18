#ifndef INCLUDE_ROADAGAIN_LOG
#define INCLUDE_ROADAGAIN_LOG

#include <vector>

#include "board.hpp"

namespace roadagain
{

void log_records(const std::vector<Cell>& logs, const CellColor& winner);

} // namespace roadagain

#endif
