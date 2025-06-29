#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include "linkerr.h"

int create_soft_link(const char *source,const char *dest) {
    if (symlink(source,dest) != 0) {
        perror("symlink failed");
        return -1;
    }
    return 0;
}

int create_hard_link(const char *source,const char *dest) {
    if (link(source,dest) != 0) {
        perror("link failed");
        return -1;
    }
    return 0;
}
