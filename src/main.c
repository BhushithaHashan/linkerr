#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <unistd.h>   // access()
#include <sys/stat.h> // stat()
#include "linkerr.h"

// Buffer sizes
#define PATH_MAX_LEN PATH_MAX
#define NAME_MAX_LEN 256


 //Expand '~' to home directory if present

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


//Normalize path: resolve "." and ".."

void normalize_path(char *path) {
    char temp[PATH_MAX_LEN];
    char *stack[PATH_MAX_LEN];
    int top = -1;

    char *token = strtok(path, "/");
    while (token != NULL) {
        if (strcmp(token, "..") == 0) {
            if (top >= 0) top--;
        } else if (strcmp(token, ".") != 0 && strlen(token) > 0) {
            stack[++top] = token;
        }
        token = strtok(NULL, "/");
    }

    temp[0] = '\0';
    for (int i = 0; i <= top; i++) {
        strcat(temp, "/");
        strcat(temp, stack[i]);
    }

    if (top == -1) strcpy(path, "/");
    else strncpy(path, temp, PATH_MAX_LEN);
}
//Interactive CLI to create soft or hard links
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

    // Source directory input
    printf("Enter source directory path:\n> ");
    if (!fgets(src_dir, PATH_MAX_LEN, stdin)) return;
    src_dir[strcspn(src_dir, "\n")] = 0;
    expand_home(src_dir, PATH_MAX_LEN);
    normalize_path(src_dir);

    // Check directory exists
    if (is_directory(src_dir) != 1) return;

    // Source file/dir name
    printf("Enter source file or directory name:\n> ");
    if (!fgets(src_name, NAME_MAX_LEN, stdin)) return;
    src_name[strcspn(src_name, "\n")] = 0;

    // Build full source path
    if (snprintf(src_full, PATH_MAX_LEN, "%s/%s", src_dir, src_name) >= PATH_MAX_LEN) {
        fprintf(stderr, "Error: Source path too long.\n");
        return;
    }

    // Target directory input
    printf("Enter target directory for the link:\n> ");
    if (!fgets(link_dir, PATH_MAX_LEN, stdin)) return;
    link_dir[strcspn(link_dir, "\n")] = 0;
    expand_home(link_dir, PATH_MAX_LEN);
    normalize_path(link_dir);

    // Check directory exists
    if (is_directory(link_dir) != 1) return;

    // Link name
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
        // Hard link directory check
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
}

/**
 * Entry point
 */
int main(void) {
    printf("Welcome to linkerr - interactive link manager\n");
    interactive_link();
    return 0;
}
