cmake_minimum_required(VERSION 3.22)
project(ml)

set(CMAKE_CXX_STANDARD 20)

find_package(OpenCV REQUIRED)
find_package(OpenMP REQUIRED)
find_package(nlohmann_json REQUIRED)

include_directories("${CMAKE_CURRENT_SOURCE_DIR}/utils")

add_executable(ml
        main.cpp
        utils/config.cpp
        utils/kernel.cpp
        utils/convolution.cpp
        utils/runner.cpp)

target_link_libraries(ml
        opencv_core
        opencv_imgcodecs
        OpenMP::OpenMP_CXX
        nlohmann_json::nlohmann_json)
