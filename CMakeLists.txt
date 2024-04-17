cmake_minimum_required(VERSION 3.27)
project(ego)

set(CMAKE_CXX_STANDARD 14)

include_directories(ego)

add_executable(ego
        ego/Tensor.cpp
        ego/Tensor.h
        ego/main.cpp)
