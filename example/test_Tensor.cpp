
#include <tbb/tbb.h>

#include <tbb/parallel_for.h>
#include <tbb/blocked_range.h>
#include <iostream>

#include "ego/Tensor.h"

// 定义一个并行处理的函数体
void demo_parallel_for() {
    tbb::parallel_for(tbb::blocked_range<int>(0, 10),
        [](tbb::blocked_range<int> range) {
            for (int i = range.begin(); i != range.end(); ++i) {
                std::cout << "处理数字 " << i 
                          << "，线程 ID: " << std::this_thread::get_id() 
                          << std::endl;
            }
        });
}

int main() {

    ego::Tensor<float> tensor_A(std::vector<float>{1, 2, 3, 4, 5, 6}, std::vector<std::size_t>{3, 2});
    ego::Tensor<float> tensor_B(std::vector<float>{1, 2, 3, 4, 5, 6}, std::vector<std::size_t>{2, 3});

    std::cout << "dot result: " << tensor_A.dot(tensor_B) << std::endl;

    std::cout << "End." << std::endl;
    return 0;
}
