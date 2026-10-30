#pragma once

#include <string>

class TempFileService {
public:
    static std::string createWorkspace(
        const std::string& lessonId
    );

    static void cleanupWorkspace(
        const std::string& workspace
    );
};