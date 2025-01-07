cmake_minimum_required(VERSION 3.26)
project(Lab05)

set(CMAKE_CXX_STANDARD 17)

add_executable(Lab05 main.cpp
        HashTable.cpp
        HashTable.h
        randomGenerator.cpp
        randomGenerator.h)
