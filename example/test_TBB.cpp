


#include <tbb/tbb.h>

#include <tbb/parallel_for.h>
#include <tbb/blocked_range.h>
#include <iostream>

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
    std::cout << "开始并行任务..." << std::endl;
    demo_parallel_for();
    std::cout << "任务完成。" << std::endl;
    return 0;
}
