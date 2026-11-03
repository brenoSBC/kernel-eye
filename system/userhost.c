#include <unistd.h>
#include <string.h>

#include "userhost.h"

void get_user_and_host_name(Userhost* user) {

    char* login = getlogin();

    if(login != NULL) {
        strncpy(user->username, login, sizeof(user->username) - 1);
    } else {
        strcpy(user->username, "user");
    }

    if(gethostname(user->hostname, sizeof(user->hostname)) != 0) {
        strcpy(user->hostname, "host");
    }
}