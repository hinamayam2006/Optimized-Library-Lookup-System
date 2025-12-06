cmake_minimum_required(VERSION 3.16)
project(OptimizedLibraryLookupSystem)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Add include directories
include_directories(
    src/DataStructures/header
    src/entities/header
    src/modules/header
    src/UI
)

# Collect all source files
file(GLOB_RECURSE SOURCES
    "src/**/*.cpp"
)

# Create executable
add_executable(LibrarySystem ${SOURCES})
