cmake_minimum_required(VERSION 3.26)
project(Lab06)

set(CMAKE_CXX_STANDARD 17)

add_executable(Lab06 main.cpp
        ParentVectorTree.cpp
        ParentVectorTree.h
        MultiwayTree.cpp
        MultiwayTree.h
        BinaryTree.cpp
        BinaryTree.h)
