cmake_minimum_required(VERSION 2.8)

project(libnazg)


set(LIB_HEADERS
    include/nazg.h
    include/nz_common.h
    include/nz_int.h
    include/nz_memory.h
    include/nz_assert.h
    include/nz_error.h
    include/nz_list.h
    include/nz_space.h)

set(LIB_SOURCES
    src/nz_list.c
    src/nz_error.c)

add_library(nazg SHARED ${LIB_HEADERS}
    ${LIB_SOURCES})

install(TARGETS nazg DESTINATION ${LIBRARY_OUTPUT_PATH})
