cmake_minimum_required(VERSION 2.8)

project(test-list)

set(SOURCE_EXE main.c)

add_executable(test-list ${SOURCE_EXE})

target_link_libraries(test-list nazg)

install(TARGETS test-list DESTINATION ${EXECUTABLE_OUTPUT_PATH})
