#include <iostream>
#include <numeric>

#include "config.h"
#include "runner.h"

int main() {
    auto preferences = config::Preferences("config.json");
    std::cout << "start with preferences:" << '\n';
    std::cout << "input_dir: " << preferences.input_dir << '\n';
    std::cout << "output_dir: " << preferences.output_dir << '\n';
    std::cout << "kernel_path: " << preferences.kernel_path << '\n';
    std::cout << "should_use_openmp: " << preferences.use_openmp << '\n';

    auto durations = runner::Run(preferences);
    std::cout << "computation durations:" << '\n';
    for (int i = 0; auto duration : durations) {
        std::cout << "№" << i << ": " << duration << " ms." << '\n';
        i++;
    }
    std::cout
        << "average: "
        << std::reduce(durations.begin(), durations.end()) / static_cast<double>(durations.size())
        << " ms." << std::endl;
    return 0;
}
