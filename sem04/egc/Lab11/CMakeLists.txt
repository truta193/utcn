cmake_minimum_required(VERSION 3.28)
project(Lab11)

set(CMAKE_CXX_STANDARD 17)

add_executable(Lab11 main.cpp camera.cpp mat3.cpp mat4.cpp vec3.cpp vec4.cpp vec2.cpp projection.cpp transform.cpp)

target_link_libraries(Lab11 SDL2)