#include "vec2.hpp"

namespace roadagain
{

Vec2::Vec2() : y(0), x(0)
{
}

Vec2::Vec2(int y, int x) : y(y), x(x)
{
}

Vec2 Vec2::operator+(const Vec2& v) const
{
    return (Vec2(y + v.y, x + v.x));
}

Vec2 Vec2::operator+=(const Vec2& v)
{
    *this = *this + v;

    return (*this);
}

Vec2 Vec2::operator-(const Vec2& v) const
{
    return (Vec2(y - v.y, x - v.x));
}

Vec2 Vec2::operator-=(const Vec2& v)
{
    *this = *this - v;

    return (*this);
}

bool Vec2::operator==(const Vec2& v) const
{
    return (y == v.y && x == v.x);
}

} // namespace roadagain
