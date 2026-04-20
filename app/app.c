#include <ncurses.h>

#include "app.h"
#include "display/display.h"

void run(void) {

    System sys = {0};

    ncurses_init();

    int max_x = getmaxx(stdscr);
    WINDOW *system_window = newwin(20, max_x, 0, 0);

    while (1) {
        update_system(&sys);
        draw_system(system_window, &sys);
        napms(500);
    }
    delwin(system_window);
    endwin();
}