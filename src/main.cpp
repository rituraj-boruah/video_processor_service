
#include "core/Pipeline.h"

#include <iostream>
#include <filesystem>
#include <string>
#include <exception>

namespace fs = std::filesystem;

int main(int argc, char* argv[]) {

    std::cout << "Video Processor Service Started\n";

    // Validate command-line arguments
    if (argc < 2 || argc > 3) {

        std::cerr
            << "Usage: video_processor_service "
            << "<input_video> [output_directory]\n";

        return 1;
    }

    try {

        // Step 1: Get input video path
        fs::path inputPath = fs::absolute(argv[1]);

        if (!fs::exists(inputPath) ||
            !fs::is_regular_file(inputPath)) {

            std::cerr
                << "Input video does not exist: "
                << inputPath.string() << "\n";

            return 1;
        }

        // Step 2: Get output directory
        fs::path outputDirectory =
            (argc == 3)
                ? fs::path(argv[2])
                : fs::path("output");

        outputDirectory = fs::absolute(outputDirectory);

        // Create output directory
        fs::create_directories(outputDirectory);

        std::cout
            << "Input: "
            << inputPath.string() << "\n";

        std::cout
            << "Output directory: "
            << outputDirectory.string() << "\n";

        // Step 3: Execute video processing pipeline
        if (!Pipeline::run(
                inputPath.string(),
                outputDirectory.string()
            )) {

            std::cerr << "Video processing failed\n";
            return 1;
        }

        std::cout
            << "Processing completed successfully\n";

        return 0;
    }
    catch (const fs::filesystem_error& error) {

        std::cerr
            << "Filesystem error: "
            << error.what() << "\n";

        return 1;
    }
    catch (const std::exception& error) {

        std::cerr
            << "Application error: "
            << error.what() << "\n";

        return 1;
    }
}
