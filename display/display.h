#include <ncurses.h>

#include "../system/system.h"

void ncurses_init(void);

void draw_header(WINDOW *window);

void draw_cpu(WINDOW *window, System *sys);