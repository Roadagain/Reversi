#include <algorithm>
#include <cctype>
#include <string>

#include "cellcolor.hpp"

namespace roadagain
{

CellColor::CellColor() : type_(CellColor::EMPTY)
{
}

CellColor::CellColor(ColorEnum type) : type_(type)
{
}

CellColor::CellColor(const char* s)
{
    std::string str(s);

    std::transform(str.begin(), str.end(), str.begin(), toupper);
    if (str == "BLACK"){
        type_ = CellColor::BLACK;
    }
    else if (str == "WHITE"){
        type_ = CellColor::WHITE;
    }
    else {
        type_ = CellColor::EMPTY;
    }
}

void CellColor::reverse()
{
    type_ = reversed();
}

CellColor CellColor::reversed() const
{
    switch (type_){
        case CellColor::BLACK:
            return (CellColor(CellColor::WHITE));
        case CellColor::WHITE:
            return (CellColor(CellColor::BLACK));
        default:
            return (CellColor());
    }
}

CellColor::operator short() const
{
    return (type_);
}

} // namespace roadagain
