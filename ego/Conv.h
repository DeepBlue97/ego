// Conv.h
// Created by peter on 5/16/24.
//

#ifndef EGO_CONV_H
#define EGO_CONV_H

#include "Tensor.h"
//#include "cstdlib"
#include <cmath>

namespace ego
{
    namespace nn
    {
        template<typename T>
        class Conv2d {
        public:


            // explicit Conv2d(std::size_t in_channel, std::size_t out_channel, std::size_t kernel_size, std::size_t padding)
            //     : in_channel(in_channel),
            //     out_channel(out_channel),
            //     kernel_size(kernel_size),
            //     padding(padding),
            //     weight(Tensor<T>(0, {out_channel, in_channel, kernel_size, kernel_size})),
            //     bias(Tensor<T>(0, {out_channel})) {}

            Conv2d(std::size_t in_channel, std::size_t out_channel, std::size_t kernel_size, std::size_t padding)
                : in_channel(in_channel),
                out_channel(out_channel),
                kernel_size(kernel_size),
                padding(padding),
                weight(Tensor<T>(0, {out_channel, in_channel, kernel_size, kernel_size})),
                bias(Tensor<T>(0, {out_channel})) 
            {
                // this->in_channel = in_channel;
                // this->out_channel = out_channel;
                // this->kernel_size = kernel_size;
                // this->padding = padding;

                // // ��ʼ��weight��bias
                // std::vector<std::size_t> weight_shape = {out_channel, in_channel, kernel_size, kernel_size};
                // std::vector<std::size_t> bias_shape = {out_channel};

                // weight = Tensor<T>(0, weight_shape);
                // bias = Tensor<T>(0, bias_shape);
            }

            Tensor<T> weight; // O I H W
            Tensor<T> bias; // O H W

            std::size_t in_channel;
            std::size_t out_channel;
            std::size_t kernel_size;
            std::size_t padding;

            Tensor<T> forward(Tensor<T> x)
            {
                // weight * x + bias
                // weight: O I H W
                // x     : B C H W
                // bias  : O H W

                // Batch
                // for (size_t b = 0; b < x.shape[0]; b++)
                // {
                //     // Height
                //     for (size_t h = (this->kernel_size-1)/2; h < x.shape[2]-(this->kernel_size-1)/2; h++)
                //     {
                //         // Width
                //         for (size_t w = (this->kernel_size-1)/2; w < x.shape[2]-(this->kernel_size-1)/2; w++)
                //         {

                //             Tensor cur_t = x.slice(std::vector<std::size_t>{
                //                 b, b+1,
                //                 0, x.shape.at(1),
                //                 h-(this->kernel_size-1)/2, h+(this->kernel_size-1)/2+1, 
                //                 w-(this->kernel_size-1)/2, w+(this->kernel_size-1)/2+1
                //             })

                //             this->weight.matmul(cur_t);

                //             Tensor<T> mat = BCHW2Mat(x, this->kernel_size);

                //             // // Out Channel
                //             // for (size_t co = 0; co < out_channel; co++)
                //             // {
                //             //     // In Channel
                //             //     for (size_t ci = 0; ci < in_channel; ci++)
                //             //     {
                //             //         // Kernel
                //             //         for (size_t kh = 0; kh < this->kernel_size; kh++)
                //             //         {
                //             //             for (size_t kw = 0; kw < this->kernel_size; kw++)
                //             //             {

                //             //             }
                //             //         }
                //             //     }
                //             // }
                //         }
                //     }
                // }
            }

            Tensor<T> BCHW2Mat(Tensor<T> x, std::size_t kernel_size)
            {
                std::vector<std::size_t> x_shape = x.shape;
                std::vector<std::size_t> target_BCHW_shape = x.shape;
                target_BCHW_shape.at(2) -= (kernel_size-1);
                target_BCHW_shape.at(3) -= (kernel_size-1);

                std::vector<std::size_t> target_shape = std::vector<std::size_t>{
                    kernel_size * kernel_size,
                    target_BCHW_shape.at(0)
                    * target_BCHW_shape.at(1)
                    * target_BCHW_shape.at(2)
                    * target_BCHW_shape.at(3)};


                Tensor<T> mat = Tensor<T>(0, target_shape);


                for (int b=0; b<x.shape.at(0); b++)
                {
                    for (int c=0; c<x.shape.at(1); c++)
                    {
                        for (int h=0; h<x.shape.at(2); h++)
                        {
                            for (int w=0; w<x.shape.at(3); w++)
                            {

                            }

                        }

                    }

                }


            }

            Tensor<T> pad(Tensor<T> &x, std::size_t padding_size, T padding_value)
            {
                // BCHW
                std::vector<std::size_t> x_shape = x.shape;
                std::vector<std::size_t> x_shape_padded = x_shape;

                std::cout << "x shape:" << x_shape_padded.at(0) << x_shape_padded.at(1) <<
                x_shape_padded.at(2) << x_shape_padded.at(3);

                x_shape_padded.at(-1) += 2*padding_size;
                x_shape_padded.at(-2) += 2*padding_size;

                std::cout << "x shape padded:" << x_shape_padded.at(0) << x_shape_padded.at(1) <<
                x_shape_padded.at(2) << x_shape_padded.at(3);

                Tensor<T> x_padded = Tensor<T>(padding_value, x_shape_padded);

                // copy x to x_padded
                for (int b=0; b < x_shape.at(0); b++) {
                    for (int c = 0; c < x_shape.at(1); c++) {
                        for (int h = 0; h < x_shape.at(2); h++) {
                            for (int w = 0; w < x_shape.at(3); w++) {
                                x_padded.at(
                                        b * x_shape_padded.at(1)*x_shape_padded.at(2)*x_shape_padded.at(3)
                                        + c * x_shape_padded.at(2)*x_shape_padded.at(3)
                                        + (h+padding_size) * x_shape_padded.at(3)
                                        + w + padding_size
                                ) = x.at(
                                        b * x_shape.at(1) * x_shape.at(2) * x_shape.at(3)
                                        + c * x_shape.at(2) * x_shape.at(3)
                                        + h * x_shape.at(3)
                                        + w
                                );
                            }
                        }
                    }
                }
//                for (int b=0; b < x_shape_padded.at(0); b++)
//                {
//                    for (int c=0; c < x_shape_padded.at(1); c++)
//                    {
//                        for (int h=0; h < x_shape_padded.at(2); h++)
//                        {
//                            for (int w=0; w < x_shape_padded.at(3); w++)
//                            {
////                                int l1_location_h = std::abs(h-int(x_shape_padded.at(2)));
////                                int l1_location_w = std::abs(w-int(x_shape_padded.at(3)));
////
////                                if (l1_location_h >= padding_size || l1_location_w >= padding_size)
////                                {
////                                    x.data.at(b)
////                                }
//                            }
//                        }
//                    }
//                }

            }

        };

    }
}

#endif //EGO_CONV_H
