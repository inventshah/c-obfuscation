# Project's name
PROJECT ( cob C )

# Specify the minimum version for CMake

cmake_minimum_required(VERSION 3.1)

# Set the output folder where your program will be created
set(CMAKE_BINARY_DIR ${CMAKE_SOURCE_DIR}/bin)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR})
set(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR}/lib)

# The following folder will be included
include_directories("${PROJECT_SOURCE_DIR}/include")
#include_directories("/usr/local/include")

add_library(${PROJECT_NAME} SHARED 
	${PROJECT_SOURCE_DIR}/src/reader.c
	${PROJECT_SOURCE_DIR}/src/utils.c
	${PROJECT_SOURCE_DIR}/src/parser.c
	${PROJECT_SOURCE_DIR}/src/writer.c
	${PROJECT_SOURCE_DIR}/src/regex_helper.c
)

target_link_libraries(${PROJECT_NAME} m)

add_executable(main ${PROJECT_SOURCE_DIR}/main.c)

target_link_libraries(main ${PROJECT_NAME})
