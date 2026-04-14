#ifndef CPU_H
#define CPU_H

#include <stdint.h>
#include <stddef.h>

typedef struct {
    char model_name[128];
} CPU_info;

typedef struct {
    uint32_t id;
    double usage;

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
} CPU_stat;

typedef struct {
    CPU_stat *cores;
    size_t num_cores;
} CPU_cores;

void calculate_core_usage(CPU_cores *cpu);

void parser_cpuinfo(CPU_info *cpu);

void parser_cpu_stat(CPU_cores *cpu);

#endif