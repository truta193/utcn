cmake_minimum_required(VERSION 3.27)
project(Lab08)

set(CMAKE_CXX_STANDARD 17)

add_executable(Lab08 main.cpp bresenham.cpp)

target_link_libraries(Lab08 SDL2)
