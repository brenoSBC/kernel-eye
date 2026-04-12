#ifndef CPU_H
#define CPU_H

#include <stdint.h>

typedef struct {
    char *model_name;
} CPU_info;

typedef struct {
    uint32_t id;
    uint64_t user;
    uint64_t nice;
    uint64_t system;
    uint64_t idle;
    uint64_t iowait;
    uint64_t irq;
    uint64_t softirq;
    uint64_t steal;
    uint64_t guest;
    uint64_t guest_nice;
} CPU_core;

typedef struct {
    CPU_core *cores;
    size_t num_cores;
} CPU;

void call_cpu_info(CPU_info *cpu);

void read_cpuinfo(CPU_info *cpu);

#endif