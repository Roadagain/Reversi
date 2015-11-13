#include <ncurses.h>
#include <utility>

#include "board.hpp"
#include "print.hpp"
#include "reversi.hpp"

namespace roadagain
{

Reversi::Reversi() : black_(2), white_(2)
{
}

Reversi::~Reversi()
{
}

void Reversi::start()
{
    print();
}

std::pair<int, int> Reversi::put()
{
    int y = 0;
    int x = 0;
    char c;


    c = getch();
    while (c != '\n'){
        switch (c){
          case 'h':
            x = (x + Board::COL - 1) % Board::COL;
            break;
          case 'j':
            y = (y + 1) % Board::ROW;
            break;
          case 'k':
            y = (y + Board::ROW - 1) % Board::ROW;
            break;
          case 'l':
            x = (x + 1) % Board::COL;
            break;
        }
        print_stone(y, x, BLACK);
        c = getch();
    }

    return (std::pair<int, int>(y, x));
}

}
