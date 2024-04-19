//
// Created by peter on 4/18/24.
//

#ifndef EGO_LINEAR_H
#define EGO_LINEAR_H

#include "Tensor.h"

namespace ego
{
    namespace nn
    {
         template<typename T>
         class Linear {

             Tensor<T> weight;
             Tensor<T> bias;

             Tensor<T> forward()
             {
                 Tensor<T> out;
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
