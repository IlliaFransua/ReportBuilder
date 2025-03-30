#include "file_storage.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <unistd.h>

#define TEST_DIRECTORY "test_catalog"
#define TEST_TARGET_TEST_FILE_PATH "target_test_file.txt"
#define TEST_SOURCE_TEST_FILE_PATH "source_test_file.txt"

void create_test_file(const char *file_name) {
    FILE *file = fopen(file_name, "wb");
    if (file) {
        const char *data = "Test data for file storage.";
        fwrite(data, 1, strlen(data), file);
        fclose(file);
    }
}

int remove_directory_if_empty(const char *directory_name) {
    DIR *dir = opendir(directory_name);
    if (dir) {
        struct dirent *entry;
        int is_empty = 1;
        while ((entry = readdir(dir)) != NULL) {
            if (entry->d_name[0] != '.') {
                is_empty = 0;
                break;
            }
        }
        closedir(dir);

        if (is_empty == 1) {
            if (rmdir(directory_name) != 0) {
                return -2;  // Error removing directory
            }
            return 1;
        }
    } else {
        return -1;  // Error opening directory
    }
    return -3;  // Directory is not empty
}

void run_file_storage_tests() {
    int result;

    result = create_directory(TEST_DIRECTORY);
    if (result != 1) {
        return;
    }

    create_test_file(TEST_SOURCE_TEST_FILE_PATH);
    result = validate_file(TEST_SOURCE_TEST_FILE_PATH);
    if (result != 1) {
        remove(TEST_SOURCE_TEST_FILE_PATH);
        return;
    }

    char *unique_path = generate_unique_path(TEST_DIRECTORY, TEST_TARGET_TEST_FILE_PATH);
    if (!unique_path) {
        remove(TEST_SOURCE_TEST_FILE_PATH);
        return;
    }

    result = save_file(TEST_SOURCE_TEST_FILE_PATH, unique_path);

    remove(TEST_SOURCE_TEST_FILE_PATH);

    if (access(unique_path, F_OK) == 0) {
        if (remove(unique_path) != 0) {
            perror("Error removing target file");
        }
    }

    free(unique_path);

    DIR *dir = opendir(TEST_DIRECTORY);
    if (dir) {
        struct dirent *entry;
        while ((entry = readdir(dir)) != NULL) {
            if (entry->d_name[0] != '.') {
                char file_path[1024];
                snprintf(file_path, sizeof(file_path), "%s/%s", TEST_DIRECTORY, entry->d_name);
                if (remove(file_path) != 0) {
                    perror("Error removing file in directory");
                }
            }
        }
        closedir(dir);
    }

    result = remove_directory_if_empty(TEST_DIRECTORY);
}
