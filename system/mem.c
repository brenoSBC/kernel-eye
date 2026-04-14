#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <inttypes.h>

#include "mem.h"

void mem_usage(Memory *mem) {
    mem->used = (mem->total - mem->available);
}

void parser_meminfo(Memory *mem) {

    FILE *file = fopen("/proc/meminfo", "r");
    if (!file) return;

    char *line = NULL;
    size_t len = 0;

    mem->total = 0;            
    mem->available = 0;

    while (getline(&line, &len, file) != -1) {
        if (strncmp(line, "MemTotal:", 9) == 0) {
            sscanf(line, "MemTotal: %"SCNu64 " kB", &mem->total);
        } else if (strncmp(line, "MemAvailable:", 13) == 0) {
            sscanf(line, "MemAvailable: %"SCNu64 " kB", &mem->available);        
        }

        if(mem->total && mem->available) break;
    }
    free(line);
    fclose(file);
}