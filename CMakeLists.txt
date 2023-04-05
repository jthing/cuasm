cmake_minimum_required(VERSION 3.22)
project(cuasm-compiler C)

set(CMAKE_C_STANDARD 11)

find_program(CPP_PATH CPP /usr/bin)

include_directories(include)
set(CMAKE_INCLUDE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/include)
add_executable(cuasm
        ${CMAKE_CURRENT_SOURCE_DIR}/src/cuasm.c
        ${CMAKE_CURRENT_SOURCE_DIR}/src/wrap.c
        ${CMAKE_INCLUDE_PATH})
add_executable(cuasm_bg
        ${CMAKE_CURRENT_SOURCE_DIR}/src/cuasm_bg.c
        ${CMAKE_CURRENT_SOURCE_DIR}/src/htoi.c
        ${CMAKE_CURRENT_SOURCE_DIR}/src/utils.c
        ${CMAKE_CURRENT_SOURCE_DIR}/src/wrap.c
        ${CMAKE_INCLUDE_PATH})

add_subdirectory(thirdparty)

option(BUILD_TESTS "Build library tests" OFF)
option(BUILD_EXAMPLES "Build example executables" OFF)

if (BUILD_TESTS)
    message(STATUS "Building tests...")
    add_subdirectory(tests)
endif()

if (BUILD_EXAMPLES)
    message(STATUS "Building examples...")
    add_subdirectory(examples)
endif()

