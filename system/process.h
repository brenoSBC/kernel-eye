#ifndef PROCESS_H
#define PROCESS_H

#include <stdint.h>

typedef struct {
    char name[256];
    int pid;
} Process;

typedef struct {
    Process *list;
    int count;
} ProcessList;

void read_process();

#endif