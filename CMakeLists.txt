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

# Source files - we'll add implementations later
set(SOURCES
    src/main.cpp
)

# Executable
add_executable(kinepredict ${SOURCES})

# Link libraries (will add LibTorch later)
target_include_directories(kinepredict PRIVATE include)

# Enable testing
enable_testing()
add_subdirectory(tests)
