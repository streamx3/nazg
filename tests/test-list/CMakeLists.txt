cmake_minimum_required(VERSION 2.8)

project(test-list)

set(LIST_TEST_HEADERS test_1.h)
set(LIST_TEST_SOURCES test_1.c
					  main.c)

add_executable(test-list ${LIST_TEST_HEADERS}
						 ${LIST_TEST_SOURCES})

target_link_libraries(test-list nazg)

install(TARGETS test-list DESTINATION ${EXECUTABLE_OUTPUT_PATH})
