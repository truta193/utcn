cmake_minimum_required(VERSION 3.25)
project(dfs C)

set(CMAKE_C_STANDARD 11)

add_executable(dfs main.c int_stack.c int_stack.h stack.c stack.h single_linked_list.c single_linked_list.h graph.c graph.h double_linked_list.c double_linked_list.h)
