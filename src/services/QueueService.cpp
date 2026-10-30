#include "services/QueueService.hpp"

#include "external/nlohmann/json.hpp"

using json = nlohmann::json;

QueueService::QueueService(const WorkerConfig& config)
    : redis(
        "tcp://" +
        config.redisHost +
        ":" +
        std::to_string(config.redisPort)
    ) {}

VideoJob QueueService::waitForJob() {
    auto result = redis.blpop("video-processing-queue", 0);

    VideoJob job;

    if (result) {
        auto payload = result->second;

        auto jsonPayload = json::parse(payload);

        job.lessonId = jsonPayload["lessonId"];
        job.r2Key = jsonPayload["r2Key"];
    }

    return job;
}