cmake_minimum_required(VERSION 3.24)
project(dll)

set(CMAKE_CXX_STANDARD 17)

add_executable(dll main.cpp DoublyLinkedList.cpp DoublyLinkedList.h)
