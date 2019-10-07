# Adding libraries
add_library(Block Block.cpp)
add_library(Column Column.cpp)
add_library(DataRecord DataRecord.cpp)
add_library(Hash Hash.cpp)
add_library(Header Header.cpp)
add_library(Heap Heap.cpp)
add_library(Schema Schema.cpp)

target_link_libraries(Heap Block)
target_link_libraries(Heap Header)
target_link_libraries(Header Schema)
target_link_libraries(Header Column)

