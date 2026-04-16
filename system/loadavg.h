#ifndef LOADAVG_H
#define LOADAVG_H

#include <stdint.h>

typedef struct {
    double m1;
    double m5;
    double m15;
    uint32_t running;
    uint32_t total;   
} LoadAvg;

void read_loadavg(LoadAvg *load);

#endif