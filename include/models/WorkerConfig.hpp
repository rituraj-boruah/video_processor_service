#pragma once

#include <string>

class WorkerConfig {
public:
    std::string redisHost;
    int redisPort;

    std::string r2Endpoint;
    std::string r2AccessKey;
    std::string r2SecretKey;
    std::string r2Bucket;

    int maxVideoSizeMb;
    int maxVideoDurationSec;
};