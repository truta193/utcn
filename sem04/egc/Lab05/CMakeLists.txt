cmake_minimum_required(VERSION 3.27)
project(Lab05)

set(CMAKE_CXX_STANDARD 17)

add_executable(Lab05 EGC_Lab5.cpp mat3.cpp mat4.cpp vec3.cpp vec4.cpp vec2.cpp transform.cpp polygon.cpp)

target_link_libraries(Lab05 SDL2)
