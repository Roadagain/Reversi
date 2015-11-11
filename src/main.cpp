#include <ncurses.h>

int main()
{
    initscr();
    cbreak();
    noecho();

    endwin();
    return (0);
}
