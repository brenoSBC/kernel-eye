#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "os.h"

void read_os_release(OS* os) {

    FILE* file = fopen("/usr/lib/os-release", "r");
    if(!file) return;

    char* line = NULL;
    size_t len = 0;

    int osname_found = 0;
    int osfamily_found = 0;

    while(getline(&line, &len, file) != -1) {
        if(strncmp(line, "PRETTY_NAME=", 12) == 0) {
            char* ptr = strchr(line, '"');
            ptr++; // jumps "
            
            strncpy(os->osname, ptr, sizeof(os->osname) - 1);
            
            size_t len = strlen(os->osname);
            os->osname[len - 2] = '\0';

            osname_found = 1;
        
        } else if (strncmp(line, "ID_LIKE=", 8) == 0) {
            sscanf(line, "ID_LIKE=%s", os->osfamily);
            
            osfamily_found = 1;
        }
        if(osname_found && osfamily_found) break;
    }
    free(line);
    fclose(file);
}


