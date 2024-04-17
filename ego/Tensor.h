//
// Created by peter on 24-4-12.
//

#ifndef EGO_TENSOR_H
#define EGO_TENSOR_H


#include <cstdlib>
#include <vector>
#include <iostream>
#include <cassert>

template<typename T>
class Tensor {

public:
    std::vector<T> data;
    std::vector<u_int> shape;

public:

    explicit Tensor(std::vector<T> data){
        this->data = data;
        assert(!data.empty());
        this->shape.push_back(data.size());
    };

    friend std::ostream& operator<<(std::ostream& os, const Tensor& obj) {
        os << "data: ";
        for (int i = 0; i < obj.data.size(); i++)
        {
            if (i < 9)
            {
                os << obj.data[i] << " ";
            }
        }
        os << std::endl;

        os << "shape: ";
        for(int i = 0; i < obj.shape.size(); i++)
        {
            os << obj.shape[i] << " ";
        }
        os << std::endl;
        return os;
    };

    void reshape(const std::vector<u_int>& _shape)
    {
        assert(!_shape.empty());
        u_int input_size = 1;
        for (const u_int & i: _shape)
        {
            input_size *= i;
        }
        assert(this->data.size()==input_size);

        this->shape = _shape;

    }

////    template<typename T>
    Tensor matmul(const Tensor<T> tensor_B)
    {
//        std::cout << this->shape.back() << std::endl;
//        std::cout << this->shape.front() << std::endl;
//        std::cout << tensor_B.shape.begin() << std::endl;
        assert(this->shape.back() == tensor_B.shape.front());
//        std::cout << "equal";

        std::vector<T> vector_C(this->data.size() * tensor_B.data.size() /
            (this->shape.back() * tensor_B.shape.front()));
        Tensor<T> tensor_C(vector_C);

//        int residual_A = this->data.size() / this->shape.back();
        int step_B = tensor_B.data.size() / tensor_B.shape.front();
        int count_C = 0;

        for (int i = 0; i < this->data.size(); i += this->shape.back())
        {
            for (int j = 0; j < step_B; j += 1)
            {
                T element_dst = 0;
                for (int k = 0; k < this->shape.back(); ++k)
                {
                    element_dst += this->data.at(i+k) * tensor_B.data.at(j+k*step_B);
                }
                tensor_C.data.at(count_C) = element_dst;
                count_C++;
            }
        }
        std::vector<u_int> shape_C;
        for (int i=0; i < this->shape.size()-1; i++)
        {
            shape_C.push_back(this->shape.at(i));
        }
        for (int i=1; i < tensor_B.shape.size(); i++)
        {
            shape_C.push_back(tensor_B.shape.at(i));
        }
        tensor_C.reshape(shape_C);
        return tensor_C;
    }
};


#endif //EGO_TENSOR_H
