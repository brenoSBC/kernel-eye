#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <inttypes.h>

#include "cpu.h"

void call_cpu_info(CPU_info *cpu) {
    read_cpuinfo(cpu);
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