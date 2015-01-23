cmake_minimum_required(VERSION 2.8)

project(test-list)

set(LIST_TEST_HEADERS	tests_nz_error.h
						tests_nz_list.h)
set(LIST_TEST_SOURCES	tests_nz_error.c
						tests_nz_list.c
						main.c)

add_executable(test-list ${LIST_TEST_HEADERS}
						 ${LIST_TEST_SOURCES})

target_link_libraries(test-list nazg)

install(TARGETS test-list DESTINATION ${EXECUTABLE_OUTPUT_PATH})
