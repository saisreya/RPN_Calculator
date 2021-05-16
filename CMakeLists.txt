# cmake_minimum_required(VERSION <specify CMake version here>)
project(PS5 C)

set(CMAKE_C_STANDARD 99)

add_executable(PS5 main.c node.h node.c stack.h stack.c rpn.h rpn.c)