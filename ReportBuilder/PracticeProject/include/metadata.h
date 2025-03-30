#ifndef METADATA_H
#define METADATA_H

#include <stddef.h>
#include <time.h>

#define MAX_FILENAME_LEN 256
#define MAX_UUID_LEN 37

typedef struct {
    char uuid[MAX_UUID_LEN];
    char filename[MAX_FILENAME_LEN];
    size_t size;
    time_t created_at;
    time_t modified_at;
} FileMetadata;

int save_metadata(const char *filepath, const FileMetadata *metadata);
int load_metadata(const char *filepath, FileMetadata *metadata);
int update_metadata(const char *filepath, const FileMetadata *metadata); 
void print_metadata(const FileMetadata *metadata);

#endif // METADATA_H
