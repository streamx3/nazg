cmake_minimum_required(VERSION 2.8)

project(libnazg)

set(HDR_PREFIX "../include/")

set(LIB_HEADER	${HDR_PREFIX}nazg.h
				${HDR_PREFIX}nz_common.h
				${HDR_PREFIX}nz_int.h
				${HDR_PREFIX}nz_memory.h
				${HDR_PREFIX}nz_assert.h
				${HDR_PREFIX}nz_error.h
				${HDR_PREFIX}nz_list.h
				${HDR_PREFIX}nz_space.h)

set(LIB_SOURCE	nz_list.c
				nz_error.c)

add_library(nazg SHARED	${LIB_HEADER}
						${LIB_SOURCE})

install(TARGETS nazg DESTINATION ${LIBRARY_OUTPUT_PATH})
