//
// Created by peter on 4/18/24.
//

#ifndef EGO_LINEAR_H
#define EGO_LINEAR_H

#include "Tensor.h"
#include "random.h"

namespace ego
{
    namespace nn
    {


         template<typename T>
         class Linear {

         public:

             explicit Linear(u_int input_size, u_int output_size){

                 using namespace ego::random;

                 weight_shape = {input_size, output_size};
                 weight = ego::random::tensor<T>(weight_shape);

                 std::vector<u_int> bias_shape = {1, output_size};
                 bias = ego::random::tensor<T>(bias_shape);
             }

             std::vector<u_int> weight_shape = {1, 1};
             Tensor<T> weight = ego::random::tensor<T>(weight_shape);
             Tensor<T> bias = ego::random::tensor<T>(weight_shape);

             Tensor<T> forward(Tensor<T> x)
             {
//                 Tensor<T> out = x.matmul(weight).add(bias);
                 Tensor<T> out = x.matmul(weight).add(bias);
                 return out;
             }

             Tensor<T> forward(Tensor<T> & x, Tensor<T> & out)
             {
                 out = x.matmul(weight).add(bias);
                 return out;
             }

             Tensor<float> backward()
             {
                 Tensor<T> out;
                 return out;
             }

         };
    }
}


#endif //EGO_LINEAR_H
