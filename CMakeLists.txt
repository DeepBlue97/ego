cmake_minimum_required(VERSION 3.27)
project(ego)

set(CMAKE_CXX_STANDARD 20)

include_directories(ego)

# Set TBB_DIR to help CMake find TBB
find_package(TBB REQUIRED)

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

# 添加 test_CBR.cpp 到目标中
add_executable(test_CBR example/test_CBR.cpp)
add_executable(test_TBB example/test_TBB.cpp)
add_executable(test_Tensor example/test_Tensor.cpp)


# 引入 TBB 的头文件目录
target_include_directories(test_TBB PRIVATE ${TBB_INCLUDE_DIRS})
target_include_directories(test_Tensor PRIVATE ${TBB_INCLUDE_DIRS})
target_include_directories(test_Tensor PRIVATE ${PROJECT_SOURCE_DIR})


# 链接 TBB 库
target_link_libraries(ego PRIVATE TBB::tbb)
target_link_libraries(test_TBB PRIVATE TBB::tbb)
target_link_libraries(test_Tensor PRIVATE TBB::tbb)
target_link_libraries(test_CBR PRIVATE TBB::tbb)


target_link_directories(test_CBR PRIVATE ${PROJECT_SOURCE_DIR})
target_link_directories(test_Tensor PRIVATE ${PROJECT_SOURCE_DIR})

# target_link_directories(test_CBR PRIVATE ${TBB_LIBRARY_DIRS})
