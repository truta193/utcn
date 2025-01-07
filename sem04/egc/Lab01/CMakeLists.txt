cmake_minimum_required(VERSION 3.27)
project(Lab01)

set(CMAKE_CXX_STANDARD 23)

add_executable(Lab01 main.cpp)

target_link_libraries(Lab01 SDL2)
