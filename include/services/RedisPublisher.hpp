#pragma once

#include <sw/redis++/redis++.h>

#include "models/ProcessingResult.hpp"
#include "models/WorkerConfig.hpp"

class RedisPublisher {
public:
    explicit RedisPublisher(const WorkerConfig& config);

    void publishResult(const ProcessingResult& result);

private:
    sw::redis::Redis redis;
};