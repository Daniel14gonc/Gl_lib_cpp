cmake_minimum_required(VERSION 3.22.1)

project(PruebaL)

add_executable(PruebaG src/shader.cpp)

add_subdirectory(gl_lib)

target_link_libraries(PruebaG gl_lib)