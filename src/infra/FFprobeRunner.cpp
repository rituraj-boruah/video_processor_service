#include "infra/FFprobeRunner.h"

#include <cstdio>
#include <iostream>
#include <array>
#include <sstream>

VideoInfo FFprobeRunner::probe(const std::string& input) {

    // 🔹 FFprobe command
    std::string cmd =
        "ffprobe -v error "
        "-select_streams v:0 "
        "-show_entries stream=width,height,r_frame_rate "
        "-show_entries format=duration "
        "-of default=noprint_wrappers=1 "
        "\"" + input + "\"";

    std::array<char, 256> buffer;
    std::string result;

    // 🔹 Run command
    FILE* pipe = _popen(cmd.c_str(), "r");
    if (!pipe) {
        std::cerr << "❌ Failed to run ffprobe\n";
        return {};
    }

    // 🔹 Read output
    while (fgets(buffer.data(), buffer.size(), pipe) != nullptr) {
        result += buffer.data();
    }

    _pclose(pipe);

    // 🔹 Parse output
    VideoInfo info{};
    std::istringstream stream(result);
    std::string line;

    int width = 0, height = 0;
    std::string fpsStr;

    while (std::getline(stream, line)) {

        if (line.find("width=") == 0) {
            width = std::stoi(line.substr(6));
        }
        else if (line.find("height=") == 0) {
            height = std::stoi(line.substr(7));
        }
        else if (line.find("r_frame_rate=") == 0) {
            fpsStr = line.substr(13);
        }
        else if (line.find("duration=") == 0) {
            info.duration = std::stod(line.substr(9));
        }
    }

    // 🔹 Build resolution
    info.resolution = std::to_string(width) + "x" + std::to_string(height);

    // 🔹 Parse FPS (e.g., 30/1)
    if (!fpsStr.empty()) {
        int num = 0, den = 1;
        sscanf(fpsStr.c_str(), "%d/%d", &num, &den);
        info.fps = (double)num / den;
    }

    return info;
}