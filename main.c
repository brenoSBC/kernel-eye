#include <stdio.h>
#include <inttypes.h>
#include <unistd.h>

#include "system/mem.h"
#include "system/cpu.h"
#include "system/userhost.h"
#include "system/uptime.h"
#include "system/kernel.h"
#include "system/os.h"

char eye_unicode[] =
    "\n"
    "\n"
    "⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢨⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀\n"
    "⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢸⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀\n"
    "⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢼⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀\n"
    "⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣿⠄⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀\n"
    "⠀⠀⠀⠀⠀⠀⠀⠀⠀⢢⠀⠀⠀⠀⠀⣿⡇⠀⠀⠀⠀⠀⠎⠀⠀⠀⠀⠀⠀⠀⠀\n"
    "⠀⠀⠀⠀⠀⡄⠀⠀⠀⠀⠘⣧⡠⣄⢺⣿⣿⠂⠄⢠⣾⠁⠀⠀⠀⠀⠀⠀⠀⠀⠀\n"
    "⠀⠀⠀⠀⠀⠀⠑⣄⢀⠀⠈⢹⣿⣄⣸⣿⣿⡤⢬⣿⡏⠀⠄⢀⡠⠊⠀⠀⠀⠀⠀\n"
    "⠀⠀⠀⠀⠀⠀⠀⠨⢻⡔⠀⣦⣿⡿⣿⣿⣿⡿⢿⣿⡄⠀⢨⣿⠁⠀⠀⠀⠀⠀⠀\n"
    "⠀⠀⠀⠀⣀⣀⣠⣶⣼⡿⠟⢿⡉⠁⠻⠿⠿⠁⠈⣹⠿⠿⣿⣍⣦⣀⣀⠀⠈⠀⠀\n"
    "⣠⣀⡤⠞⡯⢿⡟⠛⠃⠀⠀⠈⢳⣤⣀⣀⣀⣠⡼⠋⠀⡒⠀⠋⢻⣿⣶⡄⣤⡀⡄\n"
    "⠀⠀⠁⠀⠈⠙⠛⢶⣶⣶⣀⠀⠀⠀⠉⠉⠉⠁⠀⠀⠀⣐⣶⣶⡿⠛⠉⠁⠈⠀⠀\n"
    "⠀⠀⠀⠀⠀⠀⠀⠀⠫⢽⠛⣷⣮⣅⣂⣒⣒⣂⣽⣶⡿⢻⡯⡼⠀⠀⠀⠀⠀⠀⠀\n"
    "⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣀⣿⡿⠋⣿⣿⣿⡟⠻⣿⡖⡁⠈⠀⠀⠀⠀⠀⠀⠀⠀\n"
    "⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢠⡟⠢⠄⢸⣿⣿⠂⠜⠛⣧⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀\n"
    "⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⡞⠀⠀⠀⠸⣿⡟⠀⠀⠀⠙⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀\n"
    "⠀⠀⠀⠀⠀⠀⠀⠀⠀⠠⠀⠀⠀⠀⠀⣿⡇⠀⠀⡀⠀⠡⠀⠀⠀⠀⠀⠀⠀⠀⠀\n"
    "⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢠⠀⠀⣿⠁⠀⠀⡇⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀\n"
    "⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢺⠀⠀⠀⠁⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀\n"
    "⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠸⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀\n"
    "\n"
    "\n";

int main(void) {


    printf("%s", eye_unicode);

    for(int i = 5; i < 20; i++) {
        printf("\033[%d;33H", i);
        printf("│\n");
    }



    Memory mem       = {0};
    CPU_info cpuinfo = {0};
    Userhost user    = {0};
    Uptime uptime    = {0};
    Kernel kernel    = {0};
    OS os            = {0};

    read_meminfo(&mem);
    
    mem_usage(&mem);

    read_cpuinfo(&cpuinfo);

    get_user_and_host_name(&user);

    read_uptime(&uptime);

    read_osrelease(&kernel);

    read_arch(&kernel);

    read_os_release(&os);


    printf("\033[8;35H");
    printf("%s@%s", user.username, user.hostname);

    printf("\033[9;35H");
    printf("OS: %s %s", os.osname, kernel.arch);

    printf("\033[10;35H");
    printf("Kernel: %s", kernel.osrelease);

    printf("\033[11;35H");
    printf("Uptime: %zu minute(s)", uptime.boot_uptime / 60);
    
    printf("\033[12;35H");
    printf("CPU: %s", cpuinfo.model_name);

    printf("\033[13;35H");
    printf("Cache: %zumb", cpuinfo.cache_size / 1000);

    printf("\033[14;35H");
    printf("Memory: %"SCNu64"mb / %"SCNu64"mb", mem.used/1000, mem.total / 1000);
    
    printf("\033[25;1H");

    return 0;
}