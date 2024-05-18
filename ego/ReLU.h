//
// Created by peter on 4/19/24.
//

#ifndef EGO_RELU_H
#define EGO_RELU_H

#include "Tensor.h"

namespace ego
{
    namespace nn {

        template<typename T>
        class ReLU {
        public:

//            ReLU()
//            {
//
//            }

            Tensor<T> forward(Tensor<T> &x, Tensor<T> &out) {

                for (int i=0; i<x.data.size(); i++)
                {
                    if (x.data.at(i)<0)
                    {
                        out.data.at(i) = 0;
                    }
                    else
                    {
                        out.data.at(i) = x.data.at(i);
                    }
                }
                return out;

            };

            Tensor<T> backward()
            {

            }

        };


    }
}
#endif //EGO_RELU_H
