#include "config/ConfigLoader.hpp"

#include <cstdlib>

WorkerConfig ConfigLoader::load() {
    WorkerConfig config;

    config.redisHost = std::getenv("REDIS_HOST") ?: "127.0.0.1";

    const char* redisPort = std::getenv("REDIS_PORT");
    config.redisPort = redisPort ? std::stoi(redisPort) : 6379;

    config.r2Endpoint = std::getenv("R2_ENDPOINT") ?: "";
    config.r2AccessKey = std::getenv("R2_ACCESS_KEY") ?: "";
    config.r2SecretKey = std::getenv("R2_SECRET_KEY") ?: "";
    config.r2Bucket = std::getenv("R2_BUCKET") ?: "";

    const char* maxSize = std::getenv("MAX_VIDEO_SIZE_MB");
    config.maxVideoSizeMb = maxSize ? std::stoi(maxSize) : 300;

    const char* maxDuration = std::getenv("MAX_VIDEO_DURATION_SEC");
    config.maxVideoDurationSec = maxDuration ? std::stoi(maxDuration) : 900;

    return config;
}