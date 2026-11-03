#ifndef OS_H
#define OS_H

typedef struct {
    char osname[64];
    char osfamily[32];
} OS;

void read_os_release(OS* os);

#endif