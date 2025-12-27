cmake_minimum_required(VERSION 3.20)
project(KinePredict VERSION 1.0.0 LANGUAGES CXX)

# Use C++17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Compiler warnings
if(APPLE)
    add_compile_options(-Wall -Wextra -pedantic)
endif()

# Source files
add_executable(kinepredict 
    src/main.cpp
)

# Include directories
target_include_directories(kinepredict PRIVATE include)
