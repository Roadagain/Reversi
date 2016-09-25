#ifndef INCLUDE_ROADAGAIN_CELLCOLOR
#define INCLUDE_ROADAGAIN_CELLCOLOR

namespace roadagain
{

struct CellColor
{
public:
    enum ColorEnum : short
    {
        EMPTY = 1,
        BLACK,
        WHITE
    };

    CellColor();
    CellColor(ColorEnum type);
    CellColor(const char* s);

    void reverse();
    CellColor reversed() const;

    operator short() const;

private:
    ColorEnum type_;
};

} // namespace roadagain

#endif
