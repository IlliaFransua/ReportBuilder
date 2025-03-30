#ifndef UTILS_H
#define UTILS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// directory
int is_directory(const char *dirpath);

// file
int file_exists(const char *filepath);
size_t get_file_size(const char *filepath);
int remove_file(const char *filepath);
int copy_file(const char *source, const char *target);
char* get_file_extension(const char *filepath);

#endif // UTILS_H
