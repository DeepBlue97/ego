#include "Tensor.h"

//
// Created by peter on 24-4-16.
//

#include "Linear.h"
#include "ReLU.h"

int main()
{
    using namespace ego;

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

    float tensor2_index_value = tensor2.index(std::vector<unsigned int> {2,2});
    std::cout << "tensor2_index_value: " << tensor2_index_value << std::endl;

    Tensor<float> tensor2_T = Tensor<float>(0, shape2);
    tensor2_T = tensor2.transpose(0,1);
    std::cout << "tensor2_T: " << tensor2_T << std::endl;

    Tensor<float> tensor3 = tensor1.matmul(tensor2);
    std::cout << tensor3 << std::endl;


    std::vector<float> linear_x_data = {122,  94, 158};
    Tensor<float> linear_x(linear_x_data);
    linear_x.reshape(std::vector<u_int> {1, 3});
    std::cout << "linear_x: " << linear_x << std::endl;


    ego::nn::Linear<float> linear_1(3,3);
    std::cout << linear_1.weight << std::endl;
    std::cout << linear_1.bias << std::endl;

//    Tensor<float> y = linear_1.forward(tensor3);
//        linear_1.forward(tensor3);
    Tensor<float> linear_out = linear_1.forward(linear_x);
    std::cout << "linear_x: " << linear_x << std::endl;
    std::cout << "linear_out: " << linear_out << std::endl;

    linear_out = linear_1.forward(linear_x, linear_x);
    std::cout << "linear_out: " << linear_out << std::endl;
    std::cout << "linear_x: " << linear_x << std::endl;


    ego::nn::ReLU<float> relu_1 = ego::nn::ReLU<float>();

    relu_1.forward(linear_x, linear_x);

    std::cout << "linear_x: " << linear_x << std::endl;


//    Tensor<float> tensor4 = tensor2.mat(tensor3);

}