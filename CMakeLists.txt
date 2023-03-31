cmake_minimum_required(VERSION 3.25)
project(cuasm C)

set(CMAKE_C_STANDARD 11)

add_executable(cuasm cuasm.c htoi.c wrap.c)
add_executable(client client.c wrap.c)