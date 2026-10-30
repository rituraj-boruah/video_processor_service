#pragma once
#include <string>

class Encoder {
public:
    static bool encodeMultiple(const std::string& input,
                               const std::string& baseOutput);
};