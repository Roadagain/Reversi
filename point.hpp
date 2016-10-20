#ifndef INCLUDE_ROADAGAIN_POINT
#define INCLUDE_ROADAGAIN_POINT

namespace roadagain
{

struct Point
{
    int y;
    int x;

    Point();
    Point(int y, int x);

    Point operator+(const Point& p) const;
    Point operator+=(const Point& p);
    Point operator-(const Point& p) const;
    Point operator-=(const Point& p);
    bool operator==(const Point& p) const;
};

} // namespace roadagain

#endif
