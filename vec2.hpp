#ifndef INCLUDE_ROADAGAIN_VEC2
#define INCLUDE_ROADAGAIN_VEC2

namespace roadagain
{

struct Vec2
{
    int y;
    int x;

    Vec2();
    Vec2(int y, int x);

    Vec2 operator+(const Vec2& v) const;
    Vec2 operator+=(const Vec2& v);
    Vec2 operator-(const Vec2& v) const;
    Vec2 operator-=(const Vec2& v);
    bool operator==(const Vec2& v) const;
};

} // namespace roadagain

#endif
