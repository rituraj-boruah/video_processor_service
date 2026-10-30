#pragma once

#include "models/VideoJob.hpp"

class ValidationService {
public:
    static void validateJob(const VideoJob& job);
};