cmake_minimum_required(VERSION 3.16)
project(OptimizedLibraryLookupSystem)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Qt configuration
set(CMAKE_PREFIX_PATH "D:/HP/BigThings/6.10.1/mingw_64")
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

# Find Qt6
find_package(Qt6 REQUIRED COMPONENTS Core Widgets Gui)

# Add include directories for your own headers
include_directories(
    src/DataStructures/header
    src/entities/header
    src/modules/header
    src/UI
)

# Collect source files
file(GLOB_RECURSE SOURCES
    "src/DataStructures/implementation/*.cpp"
    "src/entities/implementation/*.cpp"
    "src/modules/implementation/*.cpp"
    "src/UI/LibraryGUI.cpp"
)

# Create executable
add_executable(LibrarySystem ${SOURCES} src/main.cpp)

# Link Qt libraries
target_link_libraries(LibrarySystem 
    Qt6::Core
    Qt6::Widgets
    Qt6::Gui
)

# Set Windows subsystem to hide console window
if(WIN32)
    target_link_options(LibrarySystem PRIVATE -mwindows)
endif()