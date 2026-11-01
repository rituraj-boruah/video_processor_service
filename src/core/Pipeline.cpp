
#include "core/Pipeline.h"
#include "core/Encoder.h"
#include "core/Segmenter.h"
#include "core/MetadataGenerator.h"

#include <iostream>
#include <filesystem>
#include <vector>
#include <string>

#include "utils/PlaylistGenerator.h"

namespace fs = std::filesystem;

bool Pipeline::run(
    const std::string& input,
    const std::string& outputDirectory
) {

    std::cout << "Pipeline started...\n";

    // Step 1: Validate input
    fs::path inputPath(input);

    if (!fs::exists(inputPath) ||
        !fs::is_regular_file(inputPath)) {

        std::cerr
            << "Invalid input video: "
            << input << "\n";

        return false;
    }

    // Step 2: Extract video ID
    std::string videoId = inputPath.stem().string();

    if (videoId.empty()) {
        std::cerr << "Unable to extract video ID\n";
        return false;
    }

    // Step 3: Configure output directory
    fs::path outputRoot(outputDirectory);

    fs::path baseOutputPath = outputRoot / videoId;

    std::string baseOutput = baseOutputPath.string();

    std::cout
        << "Processing video: "
        << videoId << "\n";

    std::cout
        << "Output location: "
        << baseOutput << "\n";

    // Step 4: Create directories
    fs::create_directories(baseOutputPath / "chunks");

    fs::create_directories(baseOutputPath / "1080p");
    fs::create_directories(baseOutputPath / "720p");
    fs::create_directories(baseOutputPath / "480p");

    // Step 5: Multi-resolution encoding
    if (!Encoder::encodeMultiple(input, baseOutput)) {

        std::cerr
            << "Multi-resolution encoding failed\n";

        return false;
    }

    std::cout
        << "Multi-resolution encoding completed\n";

    // Step 6: Segmentation
    std::vector<std::string> qualities = {
        "1080p",
        "720p",
        "480p"
    };

    for (const auto& quality : qualities) {

        fs::path inputVideo =
            baseOutputPath / quality / "master.mp4";

        fs::path chunkDirectory =
            baseOutputPath / quality / "chunks";

        fs::create_directories(chunkDirectory);

        if (!Segmenter::segment(
                inputVideo.string(),
                chunkDirectory.string()
            )) {

            std::cerr
                << "Segmentation failed for "
                << quality << "\n";

            return false;
        }
    }

    std::cout << "Chunking completed\n";

    // Step 7: Generate metadata
    fs::path metadataPath =
        baseOutputPath / "metadata.json";

    if (!MetadataGenerator::generateMulti(
            videoId,
            baseOutput,
            metadataPath.string()
        )) {

        std::cerr << "Metadata generation failed\n";

        return false;
    }

    std::cout << "Metadata generated\n";

    // Step 8: Generate master HLS playlist
    generateMasterPlaylist(baseOutput);

    std::cout
        << "Master playlist generation completed\n";

    std::cout
        << "Pipeline completed successfully\n";

    return true;
}
