#include <algorithm>
#include <cctype>
#include <string>

#include "cell.hpp"

namespace roadagain
{

Cell to_state(const char* s)
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

Cell reversed(Cell stone)
{
    switch (stone){
        case BLACK:
            return (WHITE);
        case WHITE:
            return (BLACK);
        default:
            return (EMPTY);
    }
}

} // namespace roadagain
