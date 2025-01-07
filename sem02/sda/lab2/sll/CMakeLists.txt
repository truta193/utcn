cmake_minimum_required(VERSION 3.24)
project(sll)

set(CMAKE_CXX_STANDARD 17)

add_executable(sll main.cpp SinglyLinkedList.cpp SinglyLinkedList.h)
