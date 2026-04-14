#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <inttypes.h>
#include <unistd.h>

#include "cpu.h"

void read_cpuinfo(CPU_info *cpu) {

    FILE *file = fopen("/proc/cpuinfo", "r");
    if (!file) return;

    char *line = NULL;
    size_t len = 0;

    while (getline(&line, &len, file) != -1) {
        if (strncmp(line, "model name", 10) == 0) {
            char *ptr = strchr(line, ':');
            ++ptr; // pula ':'
            while (*ptr == ' ') ++ptr; // pula espaços

            strncpy(cpu->model_name, ptr, sizeof(cpu->model_name) - 1);
            cpu->model_name[strcspn(ptr, "\n")] = '\0';                // pega cpu->model_name na posição que tem um '\n' e coloca um \'0' no lugar
            
            break;
        }
    }
    free(line);
    fclose(file);
}

void read_cpu_stat(CPU_cores *cpu) {

    FILE *file = fopen("/proc/stat", "r");
    if (!file) return;

    char *trash = NULL;
    char *line = NULL;
    size_t len_trash = 0;
    size_t len = 0;

    free(cpu->cores);                   // libera a memoria do realloc anterior desta funcao e depois na main faz free(struct_name.cores) para liberar o ultimo realloc
                                        // isso acontece devido a funcao calculate_core_usage chamar esta funcao
                                        // otimização (futuro): trocar por malloc, ler tudo e alocar o tamanho inteiro de uma vez
    cpu->cores = NULL;
    cpu->num_cores = 0;

    getline(&trash, &len_trash, file);

    while (getline(&line, &len, file) != -1) {
        if (strncmp(line, "cpu", 3) == 0) {

            CPU_stat stat = {0};

            sscanf(line,
                   "cpu%" SCNu32
                   "%" SCNu64
                   "%" SCNu64
                   "%" SCNu64
                   "%" SCNu64
                   "%" SCNu64
                   "%" SCNu64
                   "%" SCNu64
                   "%" SCNu64
                   "%" SCNu64
                   "%" SCNu64,
                   &stat.id,
                   &stat.user,
                   &stat.nice,
                   &stat.system,
                   &stat.idle,
                   &stat.iowait,
                   &stat.irq,
                   &stat.softirq,
                   &stat.steal,
                   &stat.guest,
                   &stat.guest_nice);

            cpu->cores = realloc(cpu->cores, sizeof(CPU_stat) * (cpu->num_cores + 1));
            cpu->cores[cpu->num_cores] = stat;
            cpu->num_cores++;
        }
    }
    free(trash);
    free(line);
    fclose(file);
}

void calculate_core_usage(CPU_cores *cpu) {

    read_cpu_stat(cpu);

    CPU_stat *prev = malloc(sizeof(CPU_stat) * cpu->num_cores);
    size_t n = cpu->num_cores;

    memcpy(prev, cpu->cores, sizeof(CPU_stat) * n);

    sleep(1);

    read_cpu_stat(cpu);

    for (size_t i = 0; i < cpu->num_cores && i < n; i++) {

        uint64_t idle_1 = prev[i].idle + prev[i].iowait;
        uint64_t idle_2 = cpu->cores[i].idle + cpu->cores[i].iowait;

        uint64_t total_1 = prev[i].user + prev[i].nice +
                           prev[i].system + prev[i].idle +
                           prev[i].iowait + prev[i].irq +
                           prev[i].softirq + prev[i].steal;

        uint64_t total_2 = cpu->cores[i].user + cpu->cores[i].nice +
                           cpu->cores[i].system + cpu->cores[i].idle +
                           cpu->cores[i].iowait + cpu->cores[i].irq +
                           cpu->cores[i].softirq + cpu->cores[i].steal;

        uint64_t idle_diff = idle_2 - idle_1;
        uint64_t total_diff = total_2 - total_1;

        if (total_diff == 0) cpu->cores[i].usage = 0.0;
        else cpu->cores[i].usage = (1.0 - (double)idle_diff / total_diff) * 100.0;
    }
    free(prev);
}
