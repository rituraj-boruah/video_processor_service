#include "services/RedisPublisher.hpp"

#include <nlohmann/json.hpp>

using json = nlohmann::json;

RedisPublisher::RedisPublisher(const WorkerConfig& config)
    : redis(
        "tcp://" +
        config.redisHost +
        ":" +
        std::to_string(config.redisPort)
    ) {}

void RedisPublisher::publishResult(
    const ProcessingResult& result
) {
    json payload;

    payload["lessonId"] = result.lessonId;

    payload["status"] =
        result.status == ProcessingStatus::COMPLETED
        ? "COMPLETED"
        : "FAILED";

    payload["message"] = result.message;

    redis.publish(
        "video-processing-results",
        payload.dump()
    );
}