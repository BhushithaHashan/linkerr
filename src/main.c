#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include "linkerr.h"
#include <unistd.h>   // for access()
#include <sys/stat.h> // for stat()

// Buffer sizes
#define PATH_MAX_LEN PATH_MAX
#define NAME_MAX_LEN 256

/**
 * Expand '~' to home directory if present
 */
void expand_home(char *path, size_t size) {
    if (path[0] == '~') {
        const char *home = getenv("HOME");
        if (!home) home = "";
        char temp[PATH_MAX_LEN];
        snprintf(temp, sizeof(temp), "%s%s", home, path + 1);
        strncpy(path, temp, size);
        path[size - 1] = '\0';
    }
}

/**
 * Interactive CLI to create soft or hard links
 */
void interactive_link(void) {
    int type;
    char src_dir[PATH_MAX_LEN];
    char src_name[NAME_MAX_LEN];
    char link_dir[PATH_MAX_LEN];
    char link_name[NAME_MAX_LEN];
    char src_full[PATH_MAX_LEN];
    char link_full[PATH_MAX_LEN];

    // Ask for link type
    printf("Choose link type:\n1) Soft link\n2) Hard link\n> ");
    if (scanf("%d", &type) != 1) {
        fprintf(stderr, "Invalid input.\n");
        return;
    }
    getchar(); // consume newline

    // Get source directory
    printf("Enter source directory path:\n> ");
    if (!fgets(src_dir, PATH_MAX_LEN, stdin)) return;
    src_dir[strcspn(src_dir, "\n")] = 0;
    expand_home(src_dir, PATH_MAX_LEN);

    // Get source file/dir name
    printf("Enter source file or directory name:\n> ");
    if (!fgets(src_name, NAME_MAX_LEN, stdin)) return;
    src_name[strcspn(src_name, "\n")] = 0;

    // Build full source path
    if (snprintf(src_full, PATH_MAX_LEN, "%s/%s", src_dir, src_name) >= PATH_MAX_LEN) {
        fprintf(stderr, "Error: Source path too long.\n");
        return;
    }

    // Get target link directory
    printf("Enter target directory for the link:\n> ");
    if (!fgets(link_dir, PATH_MAX_LEN, stdin)) return;
    link_dir[strcspn(link_dir, "\n")] = 0;
    expand_home(link_dir, PATH_MAX_LEN);

    // Get link name
    printf("Enter name for the new link:\n> ");
    if (!fgets(link_name, NAME_MAX_LEN, stdin)) return;
    link_name[strcspn(link_name, "\n")] = 0;

    // Build full link path
    if (snprintf(link_full, PATH_MAX_LEN, "%s/%s", link_dir, link_name) >= PATH_MAX_LEN) {
        fprintf(stderr, "Error: Link path too long.\n");
        return;
    }

    // Perform the link operation
    if (type == 2) {
        if (is_directory(src_full)) {
            fprintf(stderr, "\nError: Hard links to directories are prohibited.\n");
            fprintf(stderr, "Reason: To prevent filesystem cycles and corruption.\n\n");
            return;
        }
        if (create_hard_link(src_full, link_full) == 0)
            print_success(src_full, link_full, 0);
    } else if (type == 1) {
        if (create_soft_link(src_full, link_full) == 0)
            print_success(src_full, link_full, 1);
    } else {
        fprintf(stderr, "Invalid option selected.\n");
    }
    return;
}

/**
 * Entry point
 */
int main(void) {
    printf("Welcome to linkerr - interactive link manager\n");
    interactive_link();
    return 0;
}
