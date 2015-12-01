#include <ncurses.h>

#include "board.hpp"
#include "color.hpp"
#include "config.hpp"
#include "reversi.hpp"
using namespace roadagain;

int main(int argc, char** argv)
{
    Config& config = Config::instance();
    if (!config.init(argc, argv)){
        return (-1);
    }

    initscr();
    cbreak();
    noecho();
    curs_set(0);
    if (config.use_color()){
        Colors::init();
    }

    Reversi *reversi;
    reversi = new Reversi(config.player());
    reversi->play();
    getch();

    delete reversi;
    endwin();
    return (0);
}
