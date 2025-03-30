#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "metadata.h"

#define TEST_METADATA_FILE "test_metadata.dat"

FileMetadata create_test_metadata() {
    FileMetadata metadata;
    strncpy(metadata.uuid, "123e4567-e89b-12d3-a456-426614174000", MAX_UUID_LEN);
    strncpy(metadata.filename, "test_file.txt", MAX_FILENAME_LEN);
    metadata.size = 1234;
    metadata.created_at = time(NULL);
    metadata.modified_at = time(NULL);
    return metadata;
}

void test_save_metadata() {
    FileMetadata metadata = create_test_metadata();

    int result = save_metadata(TEST_METADATA_FILE, &metadata);
    assert(result == 1);

    printf("save_metadata test passed\n");
}

void test_load_metadata() {
    FileMetadata metadata = create_test_metadata();
    save_metadata(TEST_METADATA_FILE, &metadata);

    FileMetadata loaded_metadata;
    int result = load_metadata(TEST_METADATA_FILE, &loaded_metadata);
    assert(result == 1);
    assert(strcmp(metadata.uuid, loaded_metadata.uuid) == 0);
    assert(strcmp(metadata.filename, loaded_metadata.filename) == 0);
    assert(metadata.size == loaded_metadata.size);
    assert(metadata.created_at == loaded_metadata.created_at);
    assert(metadata.modified_at == loaded_metadata.modified_at);

    printf("load_metadata test passed\n");
}

void test_update_metadata() {
    FileMetadata metadata = create_test_metadata();
    save_metadata(TEST_METADATA_FILE, &metadata);

    FileMetadata updated_metadata = metadata;
    strncpy(updated_metadata.filename, "updated_file.txt", MAX_FILENAME_LEN);
    updated_metadata.size = 5678;
    updated_metadata.modified_at = time(NULL);

    int result = update_metadata(TEST_METADATA_FILE, &updated_metadata);
    assert(result == 1);

    FileMetadata loaded_metadata;
    load_metadata(TEST_METADATA_FILE, &loaded_metadata);
    assert(strcmp(updated_metadata.filename, loaded_metadata.filename) == 0);
    assert(updated_metadata.size == loaded_metadata.size);
    assert(updated_metadata.modified_at == loaded_metadata.modified_at);

    printf("update_metadata test passed\n");
}

void cleanup_metadata_file() {
    remove(TEST_METADATA_FILE);
}

void run_metadata_tests() {
    test_save_metadata();
    test_load_metadata();
    test_update_metadata();

    cleanup_metadata_file();
}
