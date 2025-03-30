#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>
#include <dirent.h>
#include <string.h>

int is_directory(const char *dirpath) {
    struct stat statbuf;

    if (stat(dirpath, &statbuf) != 0) {
        return -1;  // Path does not exist or error
    }

    return S_ISDIR(statbuf.st_mode) ? 1 : 0;  // 1 if its a directory and 0 if if its not a directory
}

int file_exists(const char *filepath) {
    struct stat statbuf;

    if (stat(filepath, &statbuf) == 0) {
        return 1;
    } else {
        return 0;
    }
}

size_t get_file_size(const char *filepath) {
    struct stat statbuf;

    if (stat(filepath, &statbuf) == 0) {
        return statbuf.st_size;
    } else {
        return (size_t)-1;
    }
}

int remove_file(const char *filepath) {
    if (file_exists(filepath) == 0) {
        return -1;  // File does not exist
    }

    if (remove(filepath) == 0) {
        return 1;
    } else {
        return -2;  // Error while deleting file
    }
}

int copy_file(const char *source, const char *target) {
    FILE *source_file = fopen(source, "rb");
    if (source_file == NULL) {
        return -1;  // Error opening source file
    }

    if (file_exists(target)) {
        return -2;  // Target file is already exists
    }

    FILE *target_file = fopen(target, "wb");
    if (target_file == NULL) {
        fclose(source_file);
        return -3;  // Error opening target file
    }

    char buffer[1024];
    size_t bytes_read;

    while ((bytes_read = fread(buffer, 1, sizeof(buffer), source_file)) > 0) {
        if (fwrite(buffer, 1, bytes_read, target_file) != bytes_read) {
            fclose(source_file);
            fclose(target_file);
            return -4;  // Error writing to target file
        }
    }

    if (ferror(source_file)) {
        fclose(source_file);
        fclose(target_file);
        return -5;  // Error reading from source file
    }

    fclose(source_file);
    fclose(target_file);

    return 1;
}

const char* get_file_extension(const char *filepath) {
    if (filepath == NULL || *filepath == '\0') {
        return NULL;
    }

    const char *pos = strrchr(filepath, '.');
    if (pos == NULL || pos == filepath) {
        return NULL;
    }

    return pos + 1;
}
