#include <ncurses.h>

#include <stdio.h>
#include <inttypes.h>

#include "display.h"

void ncurses_init(void) {
    initscr();
    noecho();
    cbreak();
    start_color();
    curs_set(0);

    init_pair(1, COLOR_WHITE, COLOR_BLACK);
    init_pair(2, COLOR_CYAN, COLOR_BLACK);
    init_pair(3, COLOR_YELLOW, COLOR_BLACK);
}

void update_system(System *sys) {
    read_cpuinfo(&sys->cpu_info);
    // calculate_core_usage(&sys->cores);
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

    // for(int i = 0; i < sys->cores.num_cores; ++i) {
    //     mvwprintw(window, ++y, 2, "Core %d: %lf ", i, sys->cores.cores[i].usage);
    // }
    // mvwprintw(window, ++y, 2, "Memory:");
    // mvwprintw(window, y, 12, "%" PRId64 "G / %" PRId64 "G",
    //           sys->mem.used, sys->mem.total);

    // wattron(window, COLOR_PAIR(2));
    // mvwprintw(window, ++y, 40, "Load Average: %.2lf %.2lf %.2lf",
    //           sys->load.m1, sys->load.m5, sys->load.m15);
    // wattroff(window, COLOR_PAIR(2));

    wrefresh(window);
}



