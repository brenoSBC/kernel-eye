#include <ncurses.h>

#include <stdio.h>
#include <inttypes.h>

#include "display.h"

void system_refresh(WINDOW *window) {

    System sys;
    int row = 0;

    parser_cpuinfo(&sys.cpu_info);
    
    parser_meminfo(&sys.mem);
    parser_meminfo(&sys.mem);
    mem_usage(&sys.mem);

    werase(window); 
    box(window, 0, 0); 

    
    mvwprintw(window, ++row, 2, "%s", sys.cpu_info.model_name);  
    mvwprintw(window, ++row, 2, "Mem: %"PRId64"G/%"PRId64"G", sys.mem.total, sys.mem.used); 

    wrefresh(window);
}

void ncurses_init() {
    
    initscr();    
    noecho();      
    cbreak();
    start_color(); 

    int max_x = getmaxx(stdscr); 
    int max_y = getmaxy(stdscr);

    init_pair(1, COLOR_GREEN, COLOR_BLACK);

    WINDOW *system_window = newwin(12, max_x, 0, 0);
    WINDOW *processes_window;


    while(1) {
        system_refresh(system_window);
        napms(500);
    }
    endwin();
}