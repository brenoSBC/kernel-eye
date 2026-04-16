#include <ncurses.h>

#include "../system/cpu.h"
#include "../system/mem.h"
#include "../system/loadavg.h"

typedef struct {
    CPU_info cpu_info;
    CPU_cores cores;
    Memory mem;
    LoadAvg load;
} System;


void system_refresh(WINDOW *window);

void ncurses_init();
