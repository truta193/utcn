cmake_minimum_required(VERSION 3.27)
project(Lab07)

set(CMAKE_CXX_STANDARD 17)

add_executable(Lab07 main.cpp vec4.cpp vec4.h mat4.cpp mat4.h vec3.cpp vec3.h mat3.cpp mat3.h vec2.cpp vec2.h clip.cpp clip.h)

target_link_libraries(Lab07 SDL2)