#pragma once

#include "models/WorkerConfig.hpp"

class ConfigLoader {
public:
    static WorkerConfig load();
};