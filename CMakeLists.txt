cmake_minimum_required(VERSION 3.30)
project(sortowanie_babel)

set(CMAKE_CXX_STANDARD 20)

add_executable(sortowanie_babel main.cpp)

MATH(EXPR stack_size "1024 * 1024 * 1024") # 1024 Mb
set(CMAKE_EXE_LINKER_FLAGS "-Wl,--stack,${stack_size}")
