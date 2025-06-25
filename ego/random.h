//
// Created by peter on 5/14/24.
//

#ifndef EGO_RANDOM_H
#define EGO_RANDOM_H

#endif //EGO_RANDOM_H

#include <random>

#include "Tensor.h"

namespace ego
{
    namespace random
    {

        template<typename T>
        T generateUniform(T min=std::numeric_limits<T>::min(), T max=std::numeric_limits<T>::max()) {
            static std::random_device rd;
            static std::mt19937 gen(rd()); // Mersenne Twister engine
            std::uniform_real_distribution<T> dis(min, max);
            return dis(gen);
        }

        template<typename T>
        T generateNormal(T mu=0, T sigma=1) {
            static std::random_device rd;
            static std::mt19937 gen(rd()); // Mersenne Twister engine
            std::normal_distribution<T> dis(mu, sigma);
            return dis(gen);
        }

        template<typename T>
        Tensor<T> tensor(std::vector<std::size_t> & shape)
        {
            assert(!shape.empty());
            std::size_t count = 1;

            for (std::size_t i : shape)
            {
                count = count * i;
            }

            assert(count>0);

            std::vector<T> data;
            for (int i=0; i<count; i++)
            {
                T e = generateNormal<T>();
                data.push_back(e);
            }

            Tensor<T> tensor = Tensor<T>(data, shape);

            return tensor;

        }
    }

}
