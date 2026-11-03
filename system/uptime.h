typedef struct {
    size_t boot_uptime;
    size_t cpu_uptime;
} Uptime;

void read_uptime(Uptime* uptime);