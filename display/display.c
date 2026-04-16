#include <ncurses.h>

#include <stdio.h>
#include <inttypes.h>

#include "display.h"

void run(void) {
    System sys = {0};

    ncurses_init();

    int max_x = getmaxx(stdscr);
    WINDOW *system_window = newwin(12, max_x, 0, 0);

    while (1) {
        update_system(&sys);
        draw_system(system_window, &sys);
        napms(500);
    }

    delwin(system_window);
    endwin();
}

void ncurses_init(void) {
    initscr();
    noecho();
    cbreak();
    start_color();

    init_pair(1, COLOR_GREEN, COLOR_BLACK);
    init_pair(2, COLOR_CYAN, COLOR_BLACK);
    init_pair(3, COLOR_YELLOW, COLOR_BLACK);
}

void update_system(System *sys) {
    read_cpuinfo(&sys->cpu_info);
    read_meminfo(&sys->mem);
    mem_usage(&sys->mem);
    read_loadavg(&sys->load);
}

void draw_system(WINDOW *window, System *sys) {
    int y = 0;

    werase(window);
    box(window, 0, 0);

    wattron(window, COLOR_PAIR(1) | A_BOLD);
    mvwprintw(window, ++y, 2, "%s", sys->cpu_info.model_name);
    wattroff(window, COLOR_PAIR(1) | A_BOLD);

    mvwprintw(window, ++y, 2, "Memory:");
    mvwprintw(window, y, 12, "%" PRId64 "G / %" PRId64 "G",
              sys->mem.used, sys->mem.total);

    wattron(window, COLOR_PAIR(2));
    mvwprintw(window, ++y, 40, "Load Average: %.2lf %.2lf %.2lf",
              sys->load.m1, sys->load.m5, sys->load.m15);
    wattroff(window, COLOR_PAIR(2));

    wrefresh(window);
}



