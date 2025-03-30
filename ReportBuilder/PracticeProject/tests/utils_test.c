#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>
#include <assert.h>
#include "utils.h"

void test_is_directory() {
    const char *dirpath = "test_dir";
    mkdir(dirpath, 0755);

    assert(is_directory(dirpath) == 1);

    rmdir(dirpath);
}

void test_file_exists() {
    const char *filepath = "test_file.txt";
    FILE *file = fopen(filepath, "w");
    fprintf(file, "Test data\n");
    fclose(file);

    assert(file_exists(filepath) == 1);

    remove(filepath);
}

void test_get_file_size() {
    const char *filepath = "test_file.txt";
    FILE *file = fopen(filepath, "w");
    fprintf(file, "Test data\n");
    fclose(file);

    assert(get_file_size(filepath) == 10);  // 10 characters

    remove(filepath);
}

void test_remove_file() {
    const char *filepath = "test_file.txt";
    FILE *file = fopen(filepath, "w");
    fprintf(file, "Test data\n");
    fclose(file);

    assert(remove_file(filepath) == 1);
    assert(file_exists(filepath) == 0);  // File should be removed
}

void test_copy_file() {
    const char *source = "source_file.txt";
    FILE *file = fopen(source, "w");
    fprintf(file, "Test data\n");
    fclose(file);

    const char *target = "target_file.txt";
    
    assert(copy_file(source, target) == 1);
    assert(file_exists(target) == 1);
    assert(get_file_size(source) == get_file_size(target));

    remove(source);
    remove(target);
}

void test_get_file_extension() {
    const char *filepath1 = "file.txt";
    assert(strcmp(get_file_extension(filepath1), "txt") == 0);

    const char *filepath2 = "file";
    assert(get_file_extension(filepath2) == NULL);

    const char *filepath3 = ".gitignore";
    assert(get_file_extension(filepath3) == NULL);
}

void run_utils_tests() {
    test_is_directory();
    test_file_exists();
    test_get_file_size();
    test_remove_file();
    test_copy_file();
    test_get_file_extension();
}
