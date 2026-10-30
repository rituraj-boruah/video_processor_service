#pragma once

#include <string>

enum class ProcessingStatus {
    COMPLETED,
    FAILED
};

class ProcessingResult {
public:
    std::string lessonId;
    ProcessingStatus status;
    std::string message;
};