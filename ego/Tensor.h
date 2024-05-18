//
// Created by peter on 24-4-12.
//

#ifndef EGO_TENSOR_H
#define EGO_TENSOR_H


#include <cstdlib>
#include <vector>
#include <iostream>
#include <cassert>

namespace ego
{
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

        explicit Tensor(std::vector<T> data, std::vector<u_int> shape){
            this->data = data;
            assert(!data.empty());
            this->shape.push_back(data.size());
            this->reshape(shape);
        };

        explicit Tensor(T value, std::vector<u_int> shape){
            // 单一值和形状初始化
//            for (u_int i : shape)
//            {
//                for (u_int j=0; j< ; j++)
//                {
//                    this->data.push_back(value);
//                }
//            }
            unsigned int ele_num = 1;
            for (unsigned int i : shape)
            {
                    ele_num *= i;
            }
            for (int i=0; i < ele_num; i++)
            {
                data.push_back(value);
            }

            this->shape = shape;
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

        std::vector<unsigned int> vi2ti(unsigned int index)
        {
            // vector index to tensor vector

            std::vector<unsigned int> ele_nums;

            for (int i = 0; i<shape.size(); i++)
            {
                unsigned int ele_num = 1;
                for (int j = i+1; j<shape.size(); j++)
                {
                    ele_num *= shape.at(j);
                }
                ele_nums.push_back(ele_num);
            }

            std::vector<unsigned int> ti;
            ti.reserve(shape.size());

            for (int i = 0; i<shape.size(); i++)
            {
                ti.push_back(index / ele_nums.at(i));
                index = index % ele_nums.at(i);
            }

            return ti;
        }

        unsigned int ti2vi(std::vector<unsigned int> index)
        {
            // tensor index to vector index
            unsigned int i_vector = 0;
            for (int i = 0; i<index.size(); i++)
            {
                unsigned int ele_num = 1;
                for (int j = i+1; j<shape.size(); j++)
                {
                    ele_num *= shape.at(j);
                }
                i_vector += index.at(i) * ele_num;
            }
            return i_vector;
        }

        T index(std::vector<unsigned int> index)
        {
            assert(index.size()==shape.size());
            return data.at(ti2vi(index));
        }

        Tensor<T> transpose(unsigned int a, unsigned int b)
        {
            std::vector<unsigned int> target_shape = shape;

            target_shape.at(a) = shape.at(b);
            target_shape.at(b) = shape.at(a);

            Tensor<T> target = Tensor<T>(0, target_shape);

//            std::vector<unsigned int> index;
//            index.reserve(target_shape.size());
//            for (int i=0; i< target_shape.size(); i++)
//            {
//                index.push_back(0);
//            }

            std::vector<unsigned int> ti_old;
            std::vector<unsigned int> ti_new;

            for(int i=0; i<data.size(); i++)
            {
                ti_new = vi2ti(i);
                ti_old = ti_new;
                std::iter_swap(ti_old.begin()+a, ti_old.begin()+b);

                target.data.at(target.ti2vi(ti_new)) = data.at(ti2vi(ti_old));
            }

            return target;
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


        Tensor& add(const Tensor<T> tensor_B)
        {

            for (int i=0; i< data.size(); i++)
            {
                data.at(i) += tensor_B.data.at(i);
            }
            return *this;
        }

        Tensor& add(const Tensor<T> tensor_B, Tensor<T>& tensor_C)
        {

            for (int i=0; i< tensor_C.data.size(); i++)
            {
                tensor_C.data.at(i) += tensor_B.data.at(i);
            }
            return tensor_C;
        }
    };

}

#endif //EGO_TENSOR_H
