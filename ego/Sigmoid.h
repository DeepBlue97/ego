//
// Created by peter on 4/18/24.
//

#ifndef EGO_SIGMOID_H
#define EGO_SIGMOID_H

#include "Tensor.h"

namespace ego
{
    template<typename T>
    class Sigmoid {

        Tensor<T> forward(Tensor<T> x)
        {
            Tensor<T> out;
            return out;
        }

        Tensor<float> backward(Tensor<T> x)
        {
            Tensor<T> out;
            return out;
        }

    };
}



#endif //EGO_SIGMOID_H
