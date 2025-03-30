add_executable(file_storage_tests
    file_storage_test.c
    metadata_test.c
    utils_test.c
    main.c
)

target_link_libraries(file_storage_tests
    file_storage
)

add_test(NAME file_storage_tests COMMAND file_storage_tests)
