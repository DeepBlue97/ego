// Module.h
//
// Created by peter on 6/26/25.
//

#ifndef EGO_MODULE_H
#define EGO_MODULE_H

#include "Tensor.h"
//#include "cstdlib"
#include <cmath>

namespace ego
{
    namespace nn
    {
        template<typename T>
        class Module
        {

            Module() = default;

            virtual ~Module() = default;

            std::vector<Module> parents;
            std::vector<Module> children;

            virtual Tensor<T> forward(const Tensor<T>& input)
            {
                return input;
            }

            // backward

            Module<T> getParents()
            {
                return this->parents;
            }

            Module<T> getChildren()
            {
                return this->children;
            }

            Module<T> setParents(const std::vector<Module<T>>& parents)
            {
                this->parents = parents;
            }

            Module<T> setChildren(const std::vector<Module<T>>& children)
            {
                this->children = children;
            }

        };
    }
}

#endif //EGO_MODULE_H
