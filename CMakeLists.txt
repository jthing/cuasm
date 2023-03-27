cmake_minimum_required(VERSION 3.24)
project(cuasm C)

set(CMAKE_C_STANDARD 11)

add_executable(cuasm main.c htoi.c htoi.h)
