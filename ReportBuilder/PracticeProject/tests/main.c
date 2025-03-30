#include <stdio.h>
#include <assert.h>

extern void run_file_storage_tests();
extern void run_metadata_tests();
extern void run_utils_tests();

int main() {
    run_file_storage_tests();
    printf("File storage tests passed!\n");

    run_metadata_tests();
    printf("Metadata tests passed!\n");

    run_utils_tests();
    printf("Utils tests passed!\n");
 
    printf("\nAll tests passed!\n");
    return 0;
}