#include "Tensor.h"

//
// Created by peter on 24-4-16.
//
int main()
{
    std::vector<float> data1 = {82,  42, 151, 183, 115,  57, 146, 136, 122};
    Tensor<float> tensor1(data1);

    std::vector<float> data2 = {122,  94, 158,  63,  69, 148, 124, 248, 164};
    Tensor<float> tensor2(data2);

    std::cout << tensor1 << std::endl;
    std::cout << tensor2 << std::endl;

    std::vector<u_int> shape1 = {3, 3};
    tensor1.reshape(shape1);
    std::cout << tensor1 << std::endl;

    std::vector<u_int> shape2 = {3, 3};
    tensor2.reshape(shape2);
    std::cout << tensor2 << std::endl;

    Tensor<float> tensor3 = tensor1.matmul(tensor2);
    std::cout << tensor3 << std::endl;

//    Tensor<float> tensor4 = tensor2.mat(tensor3);

}