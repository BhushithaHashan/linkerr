#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "linkerr.h"

#define MAX_PATH 512// Max path buffer

int main(int argc, char *argv[]) {
    //Check arguments
    if (argc != 3||strcmp(argv[1], "link")!=0) {
        printf("Usage:\n  linkerr link <source_path>\n");
        return 1;
    }

    //call interactive function
    return 0;
}
