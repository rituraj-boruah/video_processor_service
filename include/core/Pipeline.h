
#pragma once

#include <string>

class Pipeline {
public:
    static bool run(
        const std::string& input,
        const std::string& outputDirectory
    );
};
