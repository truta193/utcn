cmake_minimum_required(VERSION 3.25)
project(star C)

set(CMAKE_C_STANDARD 11)

add_executable(star main.c double_linked_list.h double_linked_list.c single_linked_list.h single_linked_list.c stack.h stack.c int_stack.h int_stack.c graph.c graph.h)
