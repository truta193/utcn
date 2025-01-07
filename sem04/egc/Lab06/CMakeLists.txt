cmake_minimum_required(VERSION 3.27)
project(Lab06)

set(CMAKE_CXX_STANDARD 17)

add_executable(Lab06 main.cpp mat3.cpp mat4.cpp vec2.cpp vec3.cpp vec4.cpp transform.cpp clip.cpp)

target_link_libraries(Lab06 SDL2)
