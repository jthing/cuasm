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
        ${CMAKE_CURRENT_SOURCE_DIR}/src/readnum.c
        ${CMAKE_CURRENT_SOURCE_DIR}/src/rbtree.c
        ${CMAKE_CURRENT_SOURCE_DIR}/src/hashtbl.c
        ${CMAKE_CURRENT_SOURCE_DIR}/src/crc32.c
        ${CMAKE_CURRENT_SOURCE_DIR}/src/crc64.c
        ${CMAKE_CURRENT_SOURCE_DIR}/src/ilog2.c
        ${CMAKE_CURRENT_SOURCE_DIR}/src/exprlib.c
        ${CMAKE_CURRENT_SOURCE_DIR}/src/saa.c
        ${CMAKE_CURRENT_SOURCE_DIR}/src/raa.c
        ${CMAKE_CURRENT_SOURCE_DIR}/src/labels.c
        ${CMAKE_CURRENT_SOURCE_DIR}/src/legacy.c
        ${CMAKE_CURRENT_SOURCE_DIR}/src/outform.c
        ${CMAKE_CURRENT_SOURCE_DIR}/src/outlib.c
        ${CMAKE_CURRENT_SOURCE_DIR}/src/outelf.c
        ${CMAKE_INCLUDE_PATH})

add_subdirectory(thirdparty)

option(BUILD_TESTS "Build library tests" OFF)
option(BUILD_EXAMPLES "Build example executables" OFF)

if (BUILD_TESTS)
    target_link_libraries(cuasm_test PRIVATE Unity EXCLUDE_FROM_ALL)
    message(STATUS "Building tests...")
    add_subdirectory(tests)
endif()

if (BUILD_EXAMPLES)
    message(STATUS "Building examples...")
    add_subdirectory(examples)
endif()

