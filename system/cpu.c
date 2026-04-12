#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <inttypes.h>

#include "cpu.h"

void call_cpu_info(CPU_info *cpu_info) {
    read_cpuinfo(cpu_info);
    read_cpu_stat(core);
}

void calculate_usage_per_core() {

}

void read_cpuinfo(CPU_info *cpu) {

    FILE *file = fopen("/proc/cpuinfo", "r");
    if(!file) return;

    char *line = NULL;
    size_t len = 0;

    cpu->model_name = NULL;

    while(getline(&line, &len, file) != -1) {
        if(strncmp(line, "model name", 10) == 0) {
            char *ptr = strchr(line, ':');
            ++ptr;                    //pula ':'
            while(*ptr == ' ') ++ptr; // pula espaços

            cpu->model_name = strdup(ptr);                           // cria memoria nova e aloca ptr em memoria nova, entao agora cpu->model aponta para uma memoria nova fora de line
                                                                     // caso contratio (cpu->model_name = ptr) quando desse free(line) cpu->model_name iria apontar para memoria ja liberada
                                                                     // dangling pointer
            cpu->model_name[strcspn(cpu->model_name, "\n")] = '\0';  // pega cpu->model_name na posição que tem um '\n' e coloca um \'0' no lugar
        }
        if(cpu->model_name) break;
    }
    free(line);
    fclose(file);

    //lembrar de dar free em cpu->model_name pois strdup aloca memoria!
}

void read_cpu_stat(CPU *cpu) {

    FILE *file = fopen("/proc/stat", "r");
    if(!file) return;

    char *trash = NULL;
    char *line = NULL;
    size_t len_trash = 0;
    size_t len = 0;

    cpu->cores = NULL;
    cpu->num_cores = 0;

    getline(&trash, &len_trash, file);

    while(getline(&line, &len, file) != -1) {
        if(strncmp(line, "cpu", 3) == 0) {

            CPU_core core = {0};

            sscanf(line, 
                "cpu%"SCNu32 
                "%"SCNu64 
                "%"SCNu64 
                "%"SCNu64 
                "%"SCNu64 
                "%"SCNu64 
                "%"SCNu64 
                "%"SCNu64 
                "%"SCNu64 
                "%"SCNu64 
                "%"SCNu64, 
                &core->id, 
                &core->user, 
                &core->nice, 
                &core->system, 
                &core->idle, 
                &core->iowait, 
                &core->irq, 
                &core->softirq, 
                &core->steal, 
                &core->guest, 
                &core->guest_nice);

                cpu->cores = realloc(cpu->cores, sizeof(CPU_core) * (cpu->num_cores + 1));
                cpu->cores[cpu->num_cores] = core;
                cpu->num_cores++;
        }      
    }
    free(trash);
    free(line);
    fclose(file);
}
