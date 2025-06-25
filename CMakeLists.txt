cmake_minimum_required(VERSION 3.27)
project(ego)

set(CMAKE_CXX_STANDARD 20)

include_directories(ego)

add_executable(ego
        ego/Tensor.cpp
        ego/Tensor.h
        ego/main.cpp
        ego/Linear.cpp
        ego/Sigmoid.h
        ego/Sigmoid.cpp
        ego/Softmax.h
        ego/Softmax.cpp
        ego/ReLU.h
        ego/ReLU.cpp
        ego/random.h
        ego/random.cpp
        ego/Conv.h
        ego/Conv.cpp)
