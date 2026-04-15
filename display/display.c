#include <stdio.h>
#include <inttypes.h>

#include "display.h"

void display(void) {
    
    System sys;

    parser_meminfo(&sys.mem);
    mem_usage(&sys.mem);
    parser_loadavg(&sys.load);

    printf("MemTotal: %"PRIu64"Gb\n", sys.mem.total/1048576);   // 1024 x 1024
    printf("MemAvailable: %"PRIu64"Gb\n", sys.mem.available/1048576);
    printf("MemUsed: %"PRIu64"Gb\n", sys.mem.used/1048576);

    printf("LoadAvg: %.2lf\n", sys.load.m1);
    printf("LoadAvg: %.2lf\n", sys.load.m5);
    printf("LoadAvg: %.2lf\n", sys.load.m15);
}

