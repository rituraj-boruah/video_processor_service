#include "core/MetadataGenerator.h"
#include "infra/FFprobeRunner.h"
#include <algorithm>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <vector>
#include <map>

#include "external/nlohmann/json.hpp"

namespace fs = std::filesystem;
using json = nlohmann::json;

bool MetadataGenerator::generateMulti(const std::string& videoId,
                                      const std::string& baseOutput,
                                      const std::string& outputPath) {

    std::vector<std::string> qualities = {"1080p", "720p", "480p"};

    json metadata;
    metadata["video_id"] = videoId;

    json qualitiesJson;

    double globalDuration = 0.0;

    for (const auto& q : qualities) {

        std::string videoPath = baseOutput + "/" + q + "/master.mp4";
        std::string chunkDir  = baseOutput + "/" + q + "/chunks";

        if (!fs::exists(videoPath) || !fs::exists(chunkDir)) {
            std::cout << "⚠️ Skipping missing quality: " << q << "\n";
            continue;
        }

        //  Probe video info
        VideoInfo info = FFprobeRunner::probe(videoPath);

        if (globalDuration == 0.0) {
            globalDuration = info.duration;
        }

        //  Collect chunks
        std::vector<std::string> chunks;

        for (const auto& entry : fs::directory_iterator(chunkDir)) {
            if (entry.is_regular_file() && entry.path().extension() == ".ts") {
              
                chunks.push_back(q + "/chunks/" + entry.path().filename().string());
            }
        }

        std::sort(chunks.begin(), chunks.end());

        //  Estimate bitrate (simple heuristic)
        int bitrate = 0;
        if (q == "1080p") bitrate = 4500;
        else if (q == "720p") bitrate = 2500;
        else if (q == "480p") bitrate = 1200;

        //  Build quality JSON
        json qData;
        qData["resolution"] = info.resolution;
        qData["fps"] = info.fps;
        qData["codec"] = "H.265";
        qData["bitrate"] = bitrate;
        qData["total_chunks"] = chunks.size();
        qData["chunks"] = chunks;

        qualitiesJson[q] = qData;
    }

    metadata["duration"] = globalDuration;
    metadata["segment_duration"] = 10;
    metadata["qualities"] = qualitiesJson;

    //  Write file
    std::ofstream file(outputPath);
    if (!file.is_open()) {
        std::cerr << " Failed to write metadata\n";
        return false;
    }

    file << metadata.dump(4);
    file.close();

    std::cout << " Multi-resolution metadata generated\n";

    return true;
}
