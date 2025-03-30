#include <stdio.h>
#include <string.h>
#include "metadata.h"

int save_metadata(const char *filepath, const FileMetadata *metadata) {
    if (filepath == NULL || metadata == NULL) {
        perror("Invalid params");
        return -1;
    }

    FILE *file = fopen(filepath, "wb");
    if (file == NULL) {
        perror("Failed to open file");
        return -1;
    }

    size_t written = fwrite(metadata, sizeof(FileMetadata), 1, file);
    if (written != 1) {
        perror("Error writing to the file");
        fclose(file);
        return -1;
    }

    if (fclose(file) != 0) {
        perror("File closure error");
        return -1;
    }

    return 1;
}

int load_metadata(const char *filepath, FileMetadata *metadata) {
    if (filepath == NULL || metadata == NULL) {
        perror("Invalid params");
        return -1;
    }

    FILE *file = fopen(filepath, "rb");
    if (file == NULL) {
        perror("Failed to open file");
        return -1;
    }

    size_t read = fread(metadata, sizeof(FileMetadata), 1, file);
    if (read != 1) {
        if (feof(file)) {
            perror("File is empty");
        } else {
            perror("Error reading from the file");
        }
        fclose(file);
        return -1;
    }

    if (fclose(file) != 0) {
        perror("File closure error");
        return -1;
    }

    return 1;
}

int update_metadata(const char *filepath, const FileMetadata *metadata) {
    if (filepath == NULL || metadata == NULL) {
        perror("Invalid params");
        return -1;
    }

    FILE *file = fopen(filepath, "r+b");
    if (file == NULL) {
        perror("Failed to open file");
        return -1;
    }

    FileMetadata current_metadata;
    size_t read = fread(&current_metadata, sizeof(FileMetadata), 1, file);
    if (read != 1) {
        if (feof(file)) {
            fprintf(stderr, "File is empty or corrupted\n");
        } else {
            perror("Error reading from the file");
        }
        fclose(file);
        return -1;
    }

    memcpy(&current_metadata, metadata, sizeof(FileMetadata));

    rewind(file);

    size_t written = fwrite(&current_metadata, sizeof(FileMetadata), 1, file);
    if (written != 1) {
        perror("Error writing to the file");
        fclose(file);
        return -1;
    }

    if (fclose(file) != 0) {
        perror("File closure error");
        return -1;
    }

    return 1;
}

void print_metadata(const FileMetadata *metadata) {
    if (metadata == NULL) {
        perror("Invalid metadata");
        return;
    }

    printf("File Metadata:\n");
    printf("  UUID: %s\n", metadata->uuid);
    printf("  Filename: %s\n", metadata->filename);
    printf("  Size: %zu bytes\n", metadata->size);
    printf("  Created at: %s", ctime(&metadata->created_at));
    printf("  Modified at: %s", ctime(&metadata->modified_at));
}