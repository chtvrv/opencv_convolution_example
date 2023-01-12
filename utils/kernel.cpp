#include "kernel.h"
#include <fstream>
#include <iostream>

namespace kernel {
    cv::Mat read_kernel(const std::string_view& kernel_path) {
        std::ifstream ifs(kernel_path.data());
        int width = 0;
        int height = 0;
        ifs >> width >> height;

        cv::Mat mat = cv::Mat::zeros(cv::Size(width,height), CV_8U);
        for (int i = 0; i < height; i++) {
            for (int j = 0; j < width; j++) {
                int value = 0;
                ifs >> value;
                mat.at<uint8_t>(i, j) = value;
            }
        }
        return mat;
    }
} // namespace kernel