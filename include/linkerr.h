#ifndef LINKERR_H
#define LINKERR_H

int create_soft_link(const char *source, const char *dest);
int create_hard_link(const char *source, const char *dest);
int is_directory(const char *path);
void print_success(const char *source, const char *dest, int is_soft);

#endif
