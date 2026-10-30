#include "services/TempFileService.hpp"

#include <filesystem>

namespace fs = std::filesystem;

std::string TempFileService::createWorkspace(
    const std::string& lessonId
) {
    std::string workspace =
        "temp/" + lessonId;

    fs::create_directories(
        workspace + "/input"
    );

    fs::create_directories(
        workspace + "/output"
    );

    fs::create_directories(
        workspace + "/logs"
    );

    return workspace;
}

void TempFileService::cleanupWorkspace(
    const std::string& workspace
) {
    if (fs::exists(workspace)) {
        fs::remove_all(workspace);
    }
}