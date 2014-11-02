cmake_minimum_required(VERSION 2.8)

project(libnazg)

set(SOURCE_LIB nz_list.c)

add_library(nazg SHARED ${SOURCE_LIB})

install(TARGETS nazg DESTINATION ${LIBRARY_OUTPUT_PATH})
