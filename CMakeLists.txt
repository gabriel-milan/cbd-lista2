cmake_minimum_required (VERSION 2.6)
project (CBD_LIST2)

# Version number
set (CBD_LIST2_VERSION_MAJOR 1)
set (CBD_LIST2_VERSION_MINOR 0)

include_directories ("${PROJECT_SOURCE_DIR}/include")
add_subdirectory (src)

add_executable(run main.cpp)

target_link_libraries (run Block)
target_link_libraries (run Column)
target_link_libraries (run DataRecord)
target_link_libraries (run Hash)
target_link_libraries (run Header)
target_link_libraries (run Heap)
target_link_libraries (run Schema)
target_link_libraries (run Sorted)