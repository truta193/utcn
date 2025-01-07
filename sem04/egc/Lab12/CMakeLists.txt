cmake_minimum_required(VERSION 3.28)
project(Lab12)

set(CMAKE_CXX_STANDARD 17)

add_executable(Lab12 main.cpp rasterization.cpp vec2.cpp vec3.cpp vec4.cpp)

target_link_libraries(Lab12 SDL2)
