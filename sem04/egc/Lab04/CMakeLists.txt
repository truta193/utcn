cmake_minimum_required(VERSION 3.27)
project(Lab04)

set(CMAKE_CXX_STANDARD 17)

add_executable(Lab04 main.cpp
testTransform.cpp
testTransform.h
transform.h
        mat3.h mat4.h vec3.h vec2.h vec4.h
        vec2.cpp vec3.cpp vec4.cpp mat3.cpp mat4.cpp
        transform.cpp)
