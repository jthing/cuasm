cmake_minimum_required(VERSION 3.22)
project(cuasm-compiler C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fuse-ld=gold")

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
target_include_directories(cuasm_bg INTERFACE
        ${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/elfutils/libasm/libasm.h
        ${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/elfutils/libdw/libdw.h
        ${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/elfutils/libebl/libebl.h
        ${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/elfutils/libdwelf/libdwelf.h)
find_library(ELFUTILS
        NAME libelf
        HINT /usr/local/lib)
target_link_libraries(cuasm_bg
        elf
        ${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/elfutils/lib/libeu.a
        ${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/elfutils/libasm/libasm_pic.a
        ${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/elfutils/libelf/libelf_pic.a
        ${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/elfutils/libebl/libebl_pic.a
        ${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/elfutils/backends/libebl_backends_pic.a
        ${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/elfutils/libdw/libdw_pic.a
        ${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/elfutils/libdwelf/libdwelf_pic.a
        ${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/elfutils/debuginfod/libdebuginfod_pic.a
        ${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/elfutils/libdwfl/libdwfl_pic.a
        ${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/elfutils/libcpu/libcpu_pic.a)

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

