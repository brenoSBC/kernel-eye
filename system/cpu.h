#ifndef CPU_H
#define CPU_H

typedef struct {
    char *model_name;
} CPU_info;


typedef struct {

} CPU_stat;

void call_cpu_info(CPU_info *cpu);

void read_cpuinfo(CPU_info *cpu);

#endif