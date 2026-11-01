#include "core/Pipeline.h"
#include "core/Encoder.h"
#include "core/Segmenter.h"
#include "core/MetadataGenerator.h"

#include <iostream>
#include <filesystem>
#include <vector>
#include "utils/PlaylistGenerator.h"

namespace fs = std::filesystem;

bool Pipeline::run(const std::string& input) {

    std::cout << " Pipeline started...\n";

    //  Extract videoId
    std::string videoId = fs::path(input).stem().string();

    //  Base output folder
    std::string baseOutput = "C:/dev_stream/video_processor/data/output/" + videoId;

    //  Create directories
    fs::create_directories(baseOutput + "/chunks");

    //  Master output path
    std::string masterOutput = baseOutput + "/master.mp4";

    // Create resolution folders
    fs::create_directories(baseOutput + "/1080p");
    fs::create_directories(baseOutput + "/720p");
    fs::create_directories(baseOutput + "/480p");

    // Step 1: Multi-resolution encode
    if (!Encoder::encodeMultiple(input, baseOutput)) {
        std::cout << " Multi-resolution encoding failed\n";
        return false;
    }

    std::cout << " Multi-resolution encoding done\n";

    //  Step 2: Segment
    std::vector<std::string> qualities = {"1080p", "720p", "480p"};

    for (const auto& q : qualities) {

        std::string inputVideo = baseOutput + "/" + q + "/master.mp4";
        std::string chunkDir   = baseOutput + "/" + q + "/chunks";

        fs::create_directories(chunkDir);

        if (!Segmenter::segment(inputVideo, chunkDir)) {
            std::cout << " Segmentation failed for " << q << "\n";
            return false;
        }
    }

    std::cout << " Chunking completed\n";

    //  Step 3: Metadata
    std::string metadataPath = baseOutput + "/metadata.json";

    if (!MetadataGenerator::generateMulti(videoId, baseOutput, metadataPath)) {
        std::cout << " Metadata generation failed\n";
        return false;
    }

    std::cout << " Metadata generated\n";

// Step 4: Generate master HLS playlist
generateMasterPlaylist(baseOutput);

std::cout << " Master playlist generated\n";

return true;
}
