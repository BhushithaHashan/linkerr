#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "linkerr.h"

#define MAX_PATH 512// Max path buffer

void interactive_link(const char *source) {
    int type;
    char dir[MAX_PATH];
    char name[MAX_PATH];

    // Ask the user for link type
    printf("Choose link type:\n1) Soft link\n2) Hard link\n> ");
    scanf("%d",&type);
    getchar();// consume newline

    //Ask target directory
    printf("Enter target directory:\n> ");
    fgets(dir, MAX_PATH, stdin);
    dir[strcspn(dir, "\n")] = 0;

    //Ask new link name
    printf("Enter new link name:\n> ");
    fgets(name,MAX_PATH,stdin);
    name[strcspn(name,"\n")] = 0;
}


int main(int argc, char *argv[]) {
    //Check arguments
    if (argc != 3||strcmp(argv[1], "link")!=0) {
        printf("Usage:\n  linkerr link <source_path>\n");
        return 1;
    }

    //call interactive function
    return 0;
}
