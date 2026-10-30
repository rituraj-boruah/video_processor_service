#pragma once
#include <string>

class FFmpegRunner {
public:
    static bool encode(const std::string& input,
                       const std::string& output);
};