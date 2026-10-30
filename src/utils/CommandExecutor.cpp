#include "utils/CommandExecutor.h"
#include <cstdlib>
#include <iostream>

int CommandExecutor::run(const std::string& command) {
    std::cout << "[CMD] " << command << std::endl;
    return system(command.c_str());
}