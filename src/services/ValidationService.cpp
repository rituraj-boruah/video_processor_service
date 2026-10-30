#include "services/ValidationService.hpp"

#include <stdexcept>

void ValidationService::validateJob(
    const VideoJob& job
) {
    if (job.lessonId.empty()) {
        throw std::runtime_error(
            "lessonId is empty"
        );
    }

    if (job.r2Key.empty()) {
        throw std::runtime_error(
            "r2Key is empty"
        );
    }

    if (
        job.r2Key.find(".mp4") ==
        std::string::npos
    ) {
        throw std::runtime_error(
            "Invalid video format"
        );
    }

    if (
        job.r2Key.find("..") !=
        std::string::npos
    ) {
        throw std::runtime_error(
            "Path traversal detected"
        );
    }
}