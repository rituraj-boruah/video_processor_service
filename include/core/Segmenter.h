#pragma once
#include <string>

class Segmenter {
public:
    static bool segment(const std::string& input,
                        const std::string& outputDir);
};