#ifndef FILE_STORAGE_H
#define FILE_STORAGE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_PATH_LEN 256
#define BUFFER_SIZE 1024
#define MAX_FILE_SIZE 5242880 // 5 MB

int validate_file(const char *file_path);
int create_directory(const char *directory_name);
char* generate_unique_path(const char *directory, const char *file_name);
int save_file(const char *source_path, const char *target_path);

#endif // FILE_STORAGE_H
