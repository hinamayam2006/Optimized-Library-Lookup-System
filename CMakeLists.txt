cmake_minimum_required(VERSION 3.16)
project(OptimizedLibraryLookupSystem)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Add include directories for your own headers
include_directories(
    src/DataStructures/header
    src/entities/header
    src/modules/header
    src/UI
)

# Explicitly add FLTK include directory
include_directories("D:/libs/fltk/install/include")

# Tell CMake where to find FLTKConfig.cmake
set(FLTK_DIR "D:/libs/fltk/install/CMake")
find_package(FLTK 1.3 REQUIRED CONFIG)

# Collect source files (exclude HashTable.cpp - it's template-only in header)
file(GLOB_RECURSE SOURCES
    "src/DataStructures/implementation/*.cpp"
    "src/entities/implementation/*.cpp"
    "src/modules/implementation/*.cpp"
    "src/UI/LibraryGUI.cpp"
)

# Create executable with GUI mode (WIN32 flag for no console window)
add_executable(LibrarySystem WIN32 ${SOURCES} src/main.cpp)

# Link FLTK libraries explicitly
target_link_libraries(LibrarySystem 
    "D:/libs/fltk/install/lib/libfltk.a"
    "D:/libs/fltk/install/lib/libfltk_forms.a"
    "D:/libs/fltk/install/lib/libfltk_images.a"
    "D:/libs/fltk/install/lib/libfltk_png.a"
    "D:/libs/fltk/install/lib/libfltk_jpeg.a"
    "D:/libs/fltk/install/lib/libfltk_z.a"
)

# Link Windows libraries that FLTK needs
target_link_libraries(LibrarySystem
    ws2_32
    comctl32
    gdi32
    ole32
    oleaut32
    uuid
    comdlg32
    advapi32
)

# Compile with GUI support
target_compile_definitions(LibrarySystem PRIVATE USE_GUI)