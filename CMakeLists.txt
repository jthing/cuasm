cmake_minimum_required(VERSION 3.25)
project(cuasm C)

set(CMAKE_C_STANDARD 11)

find_program(CPP_PATH CPP /usr/bin)

add_executable(cuasm cuasm.c wrap.c utils.c)
add_executable(cuasm_bg cuasm_be.c htoi.c wrap.c utils.c)
add_executable(client client.c wrap.c)