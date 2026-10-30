#pragma once
#include <string>

struct VideoInfo {
    double duration;
    std::string resolution;
    double fps;
};

class FFprobeRunner {
public:
    static VideoInfo probe(const std::string& input);
};
