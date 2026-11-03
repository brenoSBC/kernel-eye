#ifndef USERHOST_H
#define USERHOST_H

typedef struct {
    char username[32];
    char hostname[64];
} Userhost;

void get_user_and_host_name(Userhost* userhost);

#endif