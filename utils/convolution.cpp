#include "convolution.h"
#include <iostream>

namespace convolution {
    cv::Mat apply(const cv::Mat& kernel, const cv::Mat& src, bool use_openmp) {
        cv::Mat dst(src.rows, src.cols, src.type());

        cv::Mat flippedKernel;
        cv::flip(kernel, flippedKernel, -1);

        const int dx = kernel.cols / 2;
        const int dy = kernel.rows / 2;

        #pragma omp parallel for if(use_openmp)
        for (int i = 0; i < src.rows; i++) {
            for (int j = 0; j < src.cols; j++) {
                uint8_t tmp = 0;
                for (int k = 0; k < flippedKernel.rows; k++) {
                    for (int l = 0; l < flippedKernel.cols; l++) {
                        int x = j - dx + l;
                        int y = i - dy + k;
                        if (x >= 0 && x < src.cols && y >= 0 && y < src.rows) {
                            tmp += src.at<uint8_t>(y, x) * flippedKernel.at<uint8_t>(k, l);
                        }
                    }
                }
                dst.at<uint8_t>(i, j) = cv::saturate_cast<uint8_t>(tmp);
            }
        }
        return dst.clone();
    }
} // namespace convolution