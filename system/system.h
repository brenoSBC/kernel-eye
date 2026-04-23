#ifndef SYSTEM_H
#define SYSTEM_H

#include "cpu.h"
#include "mem.h"
#include "loadavg.h"

typedef struct {
    CPU_info cpu_info;
    CPU_cores cores;
    Memory mem;
    LoadAvg load;
} System;

void update_system(System *sys);

#endif