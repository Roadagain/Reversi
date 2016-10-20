#ifndef INCLUDE_ROADAGAIN_COLORMANAGER
#define INCLUDE_ROADAGAIN_COLORMANAGER

#include "color.hpp"

namespace roadagain
{

class ColorManager
{
public:
    static ColorManager& instance();

    void init();

    void change_color(const Color& color);

    static const Color BOARD;
    static const Color BLACK;
    static const Color WHITE;
    static const Color BLACK_CHOICE;
    static const Color WHITE_CHOICE;

private:
    void register_color(const Color& color);
    static const int BOARD_NUMBER = 1;
    static const int BLACK_NUMBER = 2;
    static const int WHITE_NUMBER = 3;
    static const int BLACK_CHOICE_NUMBER = 4;
    static const int WHITE_CHOICE_NUMBER = 5;
};

} // namespace roadagain

#endif
