cmake_minimum_required(VERSION 3.24)
project(cuasm C)

set(CMAKE_C_STANDARD 11)

add_executable(cuasm cuasm.c htoi.c)
add_executable(client client.c)