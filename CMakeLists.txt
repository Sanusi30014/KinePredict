cmake_minimum_required(VERSION 3.20)
project(KinePredict VERSION 1.0.0 LANGUAGES CXX)

# Use C++17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Compiler warnings and optimizations
if(APPLE OR UNIX)
    add_compile_options(-Wall -Wextra -pedantic)
    set(CMAKE_CXX_FLAGS_RELEASE "-O3 -march=native")
    set(CMAKE_CXX_FLAGS_DEBUG "-g -O0")
endif()

# Include directories
include_directories(${CMAKE_SOURCE_DIR}/include)

# Data structure implementations
set(DATA_STRUCTURES_SRC
    src/data_structures/Trie.cpp
    src/data_structures/BloomFilter.cpp
)

# Main executable
add_executable(kinepredict 
    src/main.cpp
    ${DATA_STRUCTURES_SRC}
)

target_include_directories(kinepredict PRIVATE include)

# Tests
enable_testing()

add_executable(test_trie tests/test_trie.cpp ${DATA_STRUCTURES_SRC})
target_include_directories(test_trie PRIVATE include)
add_test(NAME TrieTest COMMAND test_trie)

add_executable(test_bloom_filter tests/test_bloom_filter.cpp ${DATA_STRUCTURES_SRC})
target_include_directories(test_bloom_filter PRIVATE include)
add_test(NAME BloomFilterTest COMMAND test_bloom_filter)

add_executable(test_priority_queue tests/test_priority_queue.cpp)
target_include_directories(test_priority_queue PRIVATE include)
add_test(NAME PriorityQueueTest COMMAND test_priority_queue)
