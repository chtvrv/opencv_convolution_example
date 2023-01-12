#include "config.h"
#include <nlohmann/json.hpp>
#include <fstream>

namespace config {
    constexpr std::string_view INPUTS_IMAGE_OPTION = "input_dir";
    constexpr std::string_view OUTPUTS_IMAGE_OPTION = "output_dir";
    constexpr std::string_view KERNEL_FILE_OPTION = "kernel_file";
    constexpr std::string_view OPENMP_OPTION = "should_use_openmp";

    Preferences::Preferences(const std::string_view& config_path) {
        std::ifstream ifs(config_path.data());
        nlohmann::json data = nlohmann::json::parse(ifs);
        input_dir = data[INPUTS_IMAGE_OPTION];
        output_dir = data[OUTPUTS_IMAGE_OPTION];
        kernel_path = data[KERNEL_FILE_OPTION];
        use_openmp = data[OPENMP_OPTION];
    }
} // namespace config