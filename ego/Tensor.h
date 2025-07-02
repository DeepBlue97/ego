// Tensor.h
// Created by peter on 24-4-12.
//

#ifndef EGO_TENSOR_H
#define EGO_TENSOR_H


#include <cstdlib>
#include <vector>
#include <iostream>
#include <cassert>
#include <thread>
#include <functional>  // 必须包含 std::ref 所需头文件

#include <tbb/tbb.h>
#include <tbb/parallel_for.h>
#include <tbb/blocked_range.h>

namespace ego
{
    template<typename T>
    class Tensor {

    public:
        std::vector<T> data;
        std::vector<std::size_t> shape;

    public:

        Tensor() = default;

        explicit Tensor(std::vector<T> data){
            this->data = data;
            assert(!data.empty());
            this->shape.push_back(data.size());
        };

        explicit Tensor(std::vector<T> data, std::vector<std::size_t> shape){
            this->data = data;
            assert(!data.empty());
            this->shape.push_back(data.size());
            this->reshape(shape);
        };

        explicit Tensor(T value, std::vector<std::size_t> shape){
            // 单一值和形状初始化
//            for (std::size_t i : shape)
//            {
//                for (std::size_t j=0; j< ; j++)
//                {
//                    this->data.push_back(value);
//                }
//            }
            std::size_t ele_num = 1;
            for (std::size_t i : shape)
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

        void reshape(const std::vector<std::size_t>& _shape)
        {
            assert(!_shape.empty());
            std::size_t input_size = 1;
            for (const std::size_t & i: _shape)
            {
                input_size *= i;
            }
            assert(this->data.size()==input_size);

            this->shape = _shape;

        }

        std::vector<std::size_t> vi2ti(std::size_t index)
        {
            // vector index to tensor index

            std::vector<std::size_t> ele_nums;

            for (int i = 0; i<shape.size(); i++)
            {
                std::size_t ele_num = 1;
                for (int j = i+1; j<shape.size(); j++)
                {
                    ele_num *= shape.at(j);
                }
                ele_nums.push_back(ele_num);
            }

            std::vector<std::size_t> ti;
            ti.reserve(shape.size());

            for (int i = 0; i<shape.size(); i++)
            {
                ti.push_back(index / ele_nums.at(i));
                index = index % ele_nums.at(i);
            }

            return ti;
        }

        std::size_t ti2vi(std::vector<std::size_t> index)
        {
            // tensor index to vector index
            std::size_t i_vector = 0;
            for (int i = 0; i<index.size(); i++)
            {
                std::size_t ele_num = 1;
                for (int j = i+1; j<shape.size(); j++)
                {
                    ele_num *= shape.at(j);
                }
                i_vector += index.at(i) * ele_num;
            }
            return i_vector;
        }

<<<<<<< HEAD
        T& at(std::size_t index)
=======
        T index(std::vector<std::size_t> index)
>>>>>>> 62b0fcb9cb26983a8525e9f6dad9935e7e6acd4b
        {
            return data.at(index);
        }

        T& at(std::vector<std::size_t> index)
        {
            assert(index.size() == shape.size());
            return data.at(ti2vi(index));
        }

<<<<<<< HEAD
        Tensor<T> swapaxes(std::size_t a, std::size_t b)
=======
        Tensor<T> transpose(std::size_t a, std::size_t b)
>>>>>>> 62b0fcb9cb26983a8525e9f6dad9935e7e6acd4b
        {
            std::vector<std::size_t> target_shape = shape;

            target_shape.at(a) = shape.at(b);
            target_shape.at(b) = shape.at(a);

            Tensor<T> target = Tensor<T>(0, target_shape);

//            std::vector<std::size_t> index;
//            index.reserve(target_shape.size());
//            for (int i=0; i< target_shape.size(); i++)
//            {
//                index.push_back(0);
//            }

            std::vector<std::size_t> ti_old;
            std::vector<std::size_t> ti_new;

            for(int i=0; i<data.size(); i++)
            {
                ti_new = vi2ti(i);
                ti_old = ti_new;
                std::iter_swap(ti_old.begin()+a, ti_old.begin()+b);

                target.data.at(target.ti2vi(ti_new)) = data.at(ti2vi(ti_old));
            }

            return target;
        }

        // 拷贝构造函数
        Tensor(const Tensor& other) = default;

        // 拷贝赋值运算符
        Tensor& operator=(const Tensor& other) = default;

        T dot(const Tensor<T>& tensor_B)
        {
            /*
            逐元素相乘并累加
            */

            T result = 0;

            result = tbb::parallel_reduce(
                tbb::blocked_range<size_t>(0, this->data.size()),
                0,
                [&](const tbb::blocked_range<size_t>& r, T init) -> T {
                    for (size_t i = r.begin(); i != r.end(); ++i) {
                        init += this->data.at(i) * tensor_B.data.at(i);
                    }
                    return init;
                },
                std::plus<T>()
            );

            // for (size_t i=0; i<this->data.size(); i++)
            // {
            //     result += this->data.at(i) * tensor_B.data.at(i);
            // }

            return result;
        }

        static void dot(const Tensor<T>& tensor_A, const Tensor<T>& tensor_B, Tensor<T>& tensor_C, size_t i, size_t j, size_t step_B, size_t bundleRowCount_A)
        {
            /*
            输入：
                tensor_A: 矩阵A 输入矩阵
                tensor_B: 矩阵B 输入矩阵
                tensor_C: 矩阵C 返回的矩阵C
                i: 
                j: 
                step_B: 
                bundleRowCount_A: 
            
            */
            T element_dst = 0;
            for (size_t k = 0; k < tensor_A.shape.back(); ++k)
            {
                element_dst += tensor_A.data.at(i + k) * tensor_B.data.at(j + k*step_B);
            }
            // tensor_C.data.at(count_C) = element_dst;

            size_t row = i / tensor_A.shape.back();
            size_t col = j;

            tensor_C.data.at(row * step_B + col) = element_dst;
        }

        Tensor matmul(const Tensor<T>& tensor_B)
        {

            /*
            先reshape 为2维矩阵再进行矩阵乘法
            */

            assert(this->shape.back() == tensor_B.shape.front());

            std::vector<std::size_t> shape_C;
            for (size_t i=0; i < this->shape.size()-1; i++)
            {
                shape_C.push_back(this->shape.at(i));
            }
            for (size_t i=1; i < tensor_B.shape.size(); i++)
            {
                shape_C.push_back(tensor_B.shape.at(i));
            }

            Tensor<T> tensor_C(0, shape_C);

            size_t bundleRowCount_A = this->data.size() / this->shape.back();
            size_t bundleColCount_B = tensor_B.data.size() / tensor_B.shape.front();

            size_t step_B = tensor_B.data.size() / tensor_B.shape.front();
            size_t count_C = 0;


            for(size_t i = 0; i < bundleRowCount_A; i+= this->shape.back())
            {
                for(size_t j = 0; j < step_B; j++)
                {
                    
                }
            }

            // size_t num_threads = std::thread::hardware_concurrency();

            // std::vector<std::thread> threads;

            // for (size_t i = 0; i < this->data.size(); i += this->shape.back())
            // {
            //     for (size_t j = 0; j < step_B; j += 1)
            //     {
            //         T element_dst = 0;
            //         for (size_t k = 0; k < this->shape.back(); ++k)
            //         {
            //             element_dst += this->data.at(i + k) * tensor_B.data.at(j + k*step_B);
            //         }
            //         // tensor_C.data.at(count_C) = element_dst;

            //         size_t row = i / this->shape.back();
            //         size_t col = j;

            //         tensor_C.data.at(row * step_B + col) = element_dst;
            //     }
            // }
            // for (auto& thread : threads)
            // {
            //     if (thread.joinable()) {
            //         thread.join();
            //     }
            // }
            // std::vector<std::thread>().swap(threads);  // 清空并释放内存

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


        bool next_ti(std::vector<size_t> index_range, std::vector<size_t> cur_index, std::vector<size_t>& next_index, size_t cur_demension)
        {
            /*
            输入：
                index range: 索引范围, d1 start,end,d2 start,end, ...
                cur_index: 当前索引 d1, d2, d3, ...
                next_index: 下一个索引, d1, d2, d3, ...
                cur_demension: 当前维度, 0 or 1 or 2 or 3...
            返回：
                是否进位，如果最终返回为true，表示超出索引范围，next_index中的为无效索引。
            根据cur_demension是否为最后一个维度，来判断是否继续递归调用此函数。
            如果返回为true，表示需要进位，当前索引加1，再判断是否还要进位。
            */

            bool is_carry = false;

            if (cur_demension<index_range.size()-2) // 当前维度不是最后一个维度
            {
                next_index.at(cur_demension) = cur_index.at(cur_demension); // 当前维度的索引值赋给next索引

                is_carry = next_ti(index_range, cur_index, next_index, cur_demension + 1);

                if (is_carry) // 如果要进位，当前索引加1，再判断是否还要进位
                {
                    // return true;
                    next_index.at(cur_demension) = cur_index.at(cur_demension) + 1; // 如果需要进位，当前索引加1
                    if (next_index.at(cur_demension) == index_range.at(cur_demension*2+1))  // 判断加1后是否到达当前维度的终止索引值
                    {
                        next_index.at(cur_demension) = index_range.at(cur_demension*2); // 超出就回到当前维度的起始索引值
                        return true;
                    }
                    else
                    {
                        return false;
                    }
                }
                else // 如果不需要进位，返回false
                {
                    return false;
                }
            }
            else // 当前维度是最后一个维度
            {
                next_index.at(cur_demension) = cur_index.at(cur_demension) + 1;

                if (next_index.at(cur_demension) == index_range.at(cur_demension*2+1))
                {
                    next_index.at(cur_demension) = index_range.at(cur_demension*2); // 超出就回到当前维度的起始索引值
                    return true;
                }
                else
                {
                    return false;
                }
            }
        }

        Tensor& slice(std::vector<size_t> index)
        {
            // input: 
            //      index: demension 1 start, end, d2 start, end, d3 start, end, ...
            // output:
            //       slice tensor

            // 获取目标张量的shape
            std::vector<std::size_t> target_shape;

            for (size_t i=0; i<index.size()-1; i+=2)
            {
                target_shape.push_back(index.at(i+1) - index.at(i));
            }

            Tensor<T> target;

            // 获取起始索引
            std::vector<size_t> cur_index;
            for (size_t i=0; i<index.size()-1; i+=2) // 遍历目标张量的索引
            {
                cur_index.push_back(index.at(i));
            }

            target.data.push_back(this->at(cur_index));

            std::vector<size_t> next_index = cur_index;

            // 如果下一个未超出索引范围，则添加数据
            while (!next_ti(index, cur_index, next_index, 0))
            {
                target.data.push_back(this->data.at(next_index));
            }

            target.reshape(target_shape);
        }
    };
}

#endif //EGO_TENSOR_H
