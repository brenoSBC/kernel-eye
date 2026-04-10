#ifndef MEM_H
#define MEM_H

#include <stdint.h>

typedef struct {
    uint64_t total;
    uint64_t available;
    uint64_t used;
} Memory;

void call_mem(Memory *mem);

void mem_usage(Memory *mem);

void read_meminfo(Memory *mem);

#endif  