cmake_minimum_required(VERSION 2.8)

project(nazg)
set(nazg_VERSION_MAJOR 0)
set(nazg_VERSION_MINOR 1)

set(CMAKE_INSTALL_PREFIX "${nazg_SOURCE_DIR}/out/")
set(EXECUTABLE_OUTPUT_PATH "bin")
set(LIBRARY_OUTPUT_PATH "lib")

include_directories(include)

add_subdirectory(libnazg)
add_subdirectory(tests)
