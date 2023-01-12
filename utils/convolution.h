#pragma once

#include <opencv2/core.hpp>

namespace convolution {
    cv::Mat apply(const cv::Mat& kernel, const cv::Mat& src, bool use_openmp);
} // namespace convolution