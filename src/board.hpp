#ifndef INCLUDE_ROADAGAIN_PRINT_BOARD
#define INCLUDE_ROADAGAIN_PRINT_BOARD

namespace roadagain
{

class Board
{
public:
    Board();
    ~Board();

    void print(int y = 0, int x = 0);

    static const int ROW = 8;
    static const int COL = 8;

private:
    int** matrix_;
};

}

#endif
