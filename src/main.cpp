#include "core/Pipeline.h"

#include <iostream>
#include <filesystem>

namespace fs = std::filesystem;

// 🔹 Find first .mp4 file in input directory
std::string findInputVideo(const std::string& inputDir) {

    if (!fs::exists(inputDir)) {
        std::cerr << " Input directory does not exist: " << inputDir << std::endl;
        return "";
    }

    for (const auto& entry : fs::directory_iterator(inputDir)) {
        if (entry.path().extension() == ".mp4") {
            return entry.path().string();
        }
    }

    return ""; // No file found
}

int main() {

    std::cout << " Video Processor Service Started\n";

    std::string inputDir = "C:/dev_stream/video_processor/data/input/";

    // 🔹 Find input video
    std::string input = findInputVideo(inputDir);

    if (input.empty()) {
        std::cout << " No .mp4 file found in input folder\n";
        return -1;
    }

    std::cout << " Found input: " << input << std::endl;

    // 🔹 Run pipeline
    if (Pipeline::run(input)) {
        std::cout << " Processing completed successfully\n";
    } else {
        std::cout << " Processing failed\n";
    }

    return 0;
}