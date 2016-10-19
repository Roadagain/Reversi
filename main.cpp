#include <ncurses.h>

#include "board.hpp"
#include "colormanager.hpp"
#include "config.hpp"
#include "reversi.hpp"
using namespace roadagain;

int main(int argc, char** argv)
{
    Config& config = Config::instance();
    if (not config.init(argc, argv)){
        return (-1);
    }

    initscr();
    cbreak();
    noecho();
    keypad(stdscr, true);
    curs_set(0);
    if (config.color()){
        ColorManager::instance().init();
    }

    Reversi *reversi;
    reversi = new Reversi(config.player(), config.level());
    reversi->play();
    getch();

    delete reversi;
    endwin();
    return (0);
}
