#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <inttypes.h>
#include <unistd.h>

#include "loadavg.h"

void parser_loadavg(LoadAvg *load) {

    FILE *file = fopen("/proc/loadavg", "r");
    if(!file) return;

    fscanf(file, 
        "%lf" 
        "%lf" 
        "%lf" 
        "%"SCNu32 
        "/%"SCNu32, 
        &load->m1, 
        &load->m5, 
        &load->m15, 
        &load->running, 
        &load->total);
    
    fclose(file);
}