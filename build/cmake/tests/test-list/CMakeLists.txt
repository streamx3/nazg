cmake_minimum_required(VERSION 2.8)

project(test-list)

set(SRC_PREFIX ${NAZG_TESTS_DIR}test-list/)

set(LIST_TEST_HEADERS	${SRC_PREFIX}tests_nz_error.h
						${SRC_PREFIX}tests_nz_list.h)
set(LIST_TEST_SOURCES	${SRC_PREFIX}tests_nz_error.c
						${SRC_PREFIX}tests_nz_list.c
						${SRC_PREFIX}main.c)

add_executable(test-list ${LIST_TEST_HEADERS}
						 ${LIST_TEST_SOURCES})

target_link_libraries(test-list nazg)

install(TARGETS test-list DESTINATION tests)
