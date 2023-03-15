cmake_minimum_required(VERSION 3.24)
project(task1)

set(CMAKE_CXX_STANDARD 11)

add_executable(task1 src/main.cpp src/Matrix.cpp includes/Matrix.h)

include_directories(includes)