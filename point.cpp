#include "point.hpp"

namespace roadagain
{

Point::Point() : y(0), x(0)
{
}

Point::Point(int y, int x) : y(y), x(x)
{
}

Point Point::operator+(const Point& p) const
{
    return (Point(y + p.y, x + p.x));
}

Point Point::operator+=(const Point& p)
{
    *this = *this + p;

    return (*this);
}

Point Point::operator-(const Point& p) const
{
    return (Point(y - p.y, x - p.x));
}

Point Point::operator-=(const Point& p)
{
    *this = *this - p;

    return (*this);
}

bool Point::operator==(const Point& p) const
{
    return (y == p.y && x == p.x);
}

} // namespace roadagain
