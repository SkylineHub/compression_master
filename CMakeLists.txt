cmake_minimum_required(VERSION 3.21)
project(compression)

set(CMAKE_CXX_STANDARD 17)

add_executable(compression main.cpp entropy.h entropy.cpp node.h node.cpp)
