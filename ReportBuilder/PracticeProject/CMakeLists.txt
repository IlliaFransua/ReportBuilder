cmake_minimum_required(VERSION 3.10)
project(FileStorageProject C)

set(CMAKE_C_STANDARD 99)

include_directories(include)

include_directories("/opt/homebrew/opt/libsodium/include")

link_directories("/opt/homebrew/opt/libsodium/lib")

add_subdirectory(src)
add_subdirectory(tests)

enable_testing()
