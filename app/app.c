#include <ncurses.h>
#include <locale.h>

#include "../system/system.h"
#include "../display/display.h"

void run(void) {

    System sys = {0};
    setlocale(LC_ALL, "");
    ncurses_init();

    int max_x = getmaxx(stdscr);



    while (1) {
        update_system(&sys);
        napms(500);
    }
    // delwin();
    endwin();
}