#include <algorithm>
#include <cctype>
#include <string>

#include "cellcolor.hpp"

namespace roadagain
{

CellColor to_state(const char* s)
{
    std::string str(s);

    std::transform(str.begin(), str.end(), str.begin(), toupper);
    if (str == "BLACK"){
        return (BLACK);
    }
    else if (str == "WHITE"){
        return (WHITE);
    }
    else {
        return (EMPTY);
    }
}

CellColor reversed(CellColor color)
{
    switch (color){
        case BLACK:
            return (WHITE);
        case WHITE:
            return (BLACK);
        default:
            return (EMPTY);
    }
}

} // namespace roadagain
