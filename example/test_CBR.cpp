/*
Test Conv ReLU MaxPool2d



*/
#include "../ego/Conv.h"
#include "../ego/ReLU.h"
// #include "MaxPool2d.h"


int main()
{

    std::ios_base::sync_with_stdio(false);
    std::locale::global(std::locale("en_US.UTF-8")); // 设置全局 locale 为 UTF-8

    using namespace ego;
    nn::Conv2d<float> conv(3, 5, 3, 1);
    nn::ReLU<float> relu;

    std::cout << "conv.weight.at(0)修改前：" << conv.weight.at(0) << std::endl;
    conv.weight.at(0) = 1;
    std::cout << "conv.weight.at(0)修改后：" << conv.weight.at(0) << std::endl;
    std::vector<size_t> index = {0, 0, 0, 0};
    conv.weight.at(index) = 2;
    std::cout << "conv.weight.at(0)修改后：" << conv.weight.at(0) << std::endl;

    std::cout << "End." << std::endl;
}
