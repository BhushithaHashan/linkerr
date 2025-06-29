// struct stat {
//     dev_t     st_dev;     /* Device ID */
//     ino_t     st_ino;     /* Inode number */
//     nlink_t   st_nlink;   /* Number of hard links */
//     mode_t    st_mode;    /* File type + permissions */
//     uid_t     st_uid;     /* Owner UID */
//     gid_t     st_gid;     /* Owner GID */
//     dev_t     st_rdev;    /* Device ID (special files) */
//     off_t     st_size;    /* Total size */
//     blksize_t st_blksize; /* Block size */
//     blkcnt_t  st_blocks;  /* Blocks allocated */

//     struct timespec st_atim; /* Access time */
//     struct timespec st_mtim; /* Modify time */
//     struct timespec st_ctim; /* Change time */
// };


#include <sys/stat.h>
#include <stdio.h>
#include "linkerr.h"

int is_directory(const char *path) {
    struct stat st;
    if (stat(path, &st) != 0) {
        perror("stat failed");
        return -1;
    }
    return S_ISDIR(st.st_mode);
}

void print_success(const char *source, const char *dest, int is_soft) {
    printf("\n%s link created successfully!\n",
           is_soft ? "Symbolic" : "Hard");
    printf("Source: %s\n", source);
    printf("Link:   %s\n\n", dest);
}
