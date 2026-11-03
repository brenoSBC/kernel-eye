#include <stdio.h>
#include <string.h>

#include "kernel.h"

void read_osrelease(Kernel* kernel) {

    FILE* file = fopen("/proc/sys/kernel/osrelease", "r");
    if(!file) return;

    if(fgets(kernel->osrelease, sizeof(kernel->osrelease), file) != NULL) {
        
        kernel->osrelease[strcspn(kernel->osrelease, "\n")] = '\0';
    }
    fclose(file);
}

void read_arch(Kernel* kernel) {

    FILE* file = fopen("/proc/sys/kernel/arch", "r");
    if(!file) return;

    if(fgets(kernel->arch, sizeof(kernel->arch), file) != NULL) {

        kernel->arch[strcspn(kernel->arch, "\n")] = '\0';
    }
    fclose(file);
}