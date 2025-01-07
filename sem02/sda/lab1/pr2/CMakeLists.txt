cmake_minimum_required(VERSION 3.24)
project(pr2 C)

set(CMAKE_C_STANDARD 11)

add_executable(pr2 main.c vector.c vector.h)
