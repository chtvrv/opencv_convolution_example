#include <filesystem>
#include <chrono>

#include <opencv2/opencv.hpp>

#include "runner.h"
#include "convolution.h"
#include "kernel.h"

namespace runner {
    std::vector<double> Run(const config::Preferences& preferences) {
        std::vector<std::tuple<std::filesystem::path, std::string>> input_images;
        for (const auto& item : std::filesystem::directory_iterator(preferences.input_dir)) {
            if (item.is_regular_file()) {
                input_images.emplace_back(item.path(), item.path().filename().string());
            }
        }

        cv::Mat kernel = kernel::read_kernel(preferences.kernel_path);

        bool should_use_openmp = preferences.use_openmp;

        std::vector<cv::Mat> processed_images;
        std::vector<double> durations;

        for (const auto& image_path : input_images) {
            auto image = cv::imread(std::get<0>(image_path), cv::IMREAD_GRAYSCALE);
            const auto begin = std::chrono::high_resolution_clock::now();
            auto processed = convolution::apply(kernel, image, should_use_openmp);
            const auto end = std::chrono::high_resolution_clock::now();
            const auto elapsed_time = std::chrono::duration_cast<std::chrono::duration<double>>(end - begin);
            durations.push_back(elapsed_time.count() / 1e-3);
            processed_images.push_back(std::move(convolution::apply(kernel, image, should_use_openmp)));
        }

        std::string output_dir = preferences.output_dir;
        std::filesystem::create_directories(output_dir);
        for (int i = 0; const auto& processed_image : processed_images) {
            std::string path = output_dir + "/" + "processed_" + std::get<1>(input_images[i]);
            cv::imwrite(path, processed_image);
            i++;
        }

        return durations;
    }
};
