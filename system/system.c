#include "system.h"

void update_system(System *sys) {
    read_cpuinfo(&sys->cpu_info);
    calculate_core_usage(&sys->cores);
    read_meminfo(&sys->mem);
    mem_usage(&sys->mem);
    read_loadavg(&sys->load);
}