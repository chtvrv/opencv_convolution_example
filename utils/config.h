#pragma once

#include <tuple>
#include <string>
#include <vector>

namespace config {
    struct Preferences {
        explicit Preferences(const std::string_view& config_path);
        ~Preferences() = default;
        std::string input_dir;
        std::string output_dir;
        std::string kernel_path;
        bool use_openmp;
        bool measure_time;
    };
} // namespace config