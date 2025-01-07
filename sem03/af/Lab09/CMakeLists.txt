cmake_minimum_required(VERSION 3.26)
project(Lab09)

set(CMAKE_CXX_STANDARD 17)

add_executable(Lab09 main.cpp
        DisjointSet.cpp
        DisjointSet.h
        Node.h
        AdjList.h
)
