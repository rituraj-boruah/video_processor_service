#pragma once

#include <sw/redis++/redis++.h>

#include "models/VideoJob.hpp"
#include "models/WorkerConfig.hpp"

class QueueService {
public:
    explicit QueueService(const WorkerConfig& config);

    VideoJob waitForJob();

private:
    sw::redis::Redis redis;
};