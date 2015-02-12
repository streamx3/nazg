cmake_minimum_required(VERSION 2.8)

project(nazg)
set(nazg_VERSION_MAJOR 0)
set(nazg_VERSION_MINOR 1)

set(NAZG_PROJ_ROOT ${CMAKE_CURRENT_SOURCE_DIR}/../..)

if(${CMAKE_BUILD_TYPE} MATCHES "Release")
	# Output directory
	set(CMAKE_INSTALL_PREFIX ${NAZG_PROJ_ROOT}/out/cmake/release)
	# Debuging variable
	MESSAGE( STATUS "CMAKE_BUILD_TYPE: " ${CMAKE_BUILD_TYPE} )
else()
	# output directory
	set(CMAKE_INSTALL_PREFIX ${NAZG_PROJ_ROOT}/out/cmake/debug)
	# Debuging variables
	get_cmake_property(_variableNames VARIABLES)
	foreach (_variableName ${_variableNames})
		message(STATUS "${_variableName}=${${_variableName}}")
	endforeach()
endif()

set(EXECUTABLE_OUTPUT_PATH "bin")
set(LIBRARY_OUTPUT_PATH "lib")

include_directories(${NAZG_PROJ_ROOT}/include)

add_subdirectory(libnazg)
add_subdirectory(tests)
