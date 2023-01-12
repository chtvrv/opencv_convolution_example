#pragma once

#include <opencv2/core.hpp>

namespace kernel {
    cv::Mat read_kernel(const std::string_view& kernel_path);
} // namespace kernel