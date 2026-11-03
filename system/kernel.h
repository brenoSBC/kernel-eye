#ifndef KERNEL_H
#define KERNEL_H

typedef struct {
    char osrelease[64];
    char arch[32];    
} Kernel;

void read_osrelease(Kernel* kernel);

void read_arch(Kernel* kernel);

#endif