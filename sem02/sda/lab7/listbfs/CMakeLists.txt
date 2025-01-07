cmake_minimum_required(VERSION 3.24)
project(listbfs C)

set(CMAKE_C_STANDARD 11)

add_executable(listbfs main.c single_linked_list.c single_linked_list.h queue.c queue.h graph.c graph.h)
