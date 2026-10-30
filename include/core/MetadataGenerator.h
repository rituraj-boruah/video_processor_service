#pragma once
#include <string>

class MetadataGenerator {
public:
    static bool generateMulti(const std::string& videoId,
                              const std::string& baseOutput,
                              const std::string& outputPath);
};