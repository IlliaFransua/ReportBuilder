#include "file_storage.h"
#include "file_storage_errors.h"
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int validate_file(const char *file_path) {
    struct stat file_info;
    
    if (stat(file_path, &file_info) != 0) {
        return FILE_ERROR_STATUS;
    }

    if (file_info.st_size <= 0) {
        return FILE_EMPTY_OR_NOT_EXIST;
    }

    if (file_info.st_size > MAX_FILE_SIZE) {
        return FILE_TOO_LARGE;
    }

    return 1;
}

int create_directory(const char *directory_name) {
    struct stat stat_info;
    
    if (stat(directory_name, &stat_info) == -1) {
        if (mkdir(directory_name, 0755) != 0) {
            return DIR_ERROR_CREATE;
        }
    }
    return 1;
}

char* generate_unique_path(const char *directory, const char *file_name) {
    time_t raw_time = time(NULL);
    char time_str[20];
    
    strftime(time_str, sizeof(time_str), "%Y%m%d_%H%M%S", localtime(&raw_time));

    if (strlen(directory) + strlen(file_name) + strlen(time_str) + 2 > MAX_PATH_LEN) {
        return PATH_TOO_LONG;
    }

    char *unique_path = (char*)malloc(MAX_PATH_LEN);
    if (!unique_path) {
        return MEMORY_ALLOCATION_ERROR;
    }

    snprintf(unique_path, MAX_PATH_LEN, "%s/%s_%s", directory, time_str, file_name);
    
    return unique_path;
}

int save_file(const char *source_path, const char *target_path) {
    FILE *source_file = fopen(source_path, "rb");
    if (!source_file) {
        return FILE_ERROR_OPEN_SOURCE;
    }

    FILE *target_file = fopen(target_path, "wb");
    if (!target_file) {
        fclose(source_file);
        return FILE_ERROR_OPEN_TARGET;
    }

    char buffer[BUFFER_SIZE];
    size_t bytes;
    while ((bytes = fread(buffer, 1, BUFFER_SIZE, source_file)) > 0) {
        if (fwrite(buffer, 1, bytes, target_file) != bytes) {
            fclose(source_file);
            fclose(target_file);
            return FILE_ERROR_WRITE;
        }
    }

    fclose(source_file);
    fclose(target_file);

    return 1;
}
