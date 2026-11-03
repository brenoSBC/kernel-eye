#include <stdio.h>
#include <string.h>

#include "uptime.h"

void read_uptime(Uptime* uptime) {

    FILE* file = fopen("/proc/uptime", "r");
    if(!file) return;

    char line[64];

    if(fgets(line, sizeof(line), file) != NULL) {
        line[strcspn(line, "\n")] = '\0';

        sscanf(line, "%zu %zu", &uptime->boot_uptime, &uptime->cpu_uptime);
    }
    fclose(file);
}