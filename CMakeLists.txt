
cmake_minimum_required(VERSION 3.22)

project(video_processor_service
    LANGUAGES CXX
)

# ==========================================
# C++ Configuration
# ==========================================

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# ==========================================
# Dependencies
# ==========================================

# Hiredis: C client library for Redis
find_package(hiredis CONFIG REQUIRED)

# Redis++: C++ client library for Redis
find_package(redis++ CONFIG REQUIRED)

# Thread support
find_package(Threads REQUIRED)

# ==========================================
# Source Files
# ==========================================

set(VIDEO_PROCESSOR_SOURCES

    src/main.cpp

    # Core
    src/core/Encoder.cpp
    src/core/Segmenter.cpp
    src/core/Pipeline.cpp
    src/core/MetadataGenerator.cpp

    # Infrastructure
    src/infra/FFmpegRunner.cpp
    src/infra/FFprobeRunner.cpp

    # Utilities
    src/utils/CommandExecutor.cpp
    src/utils/PlaylistGenerator.cpp

    # Configuration
    src/config/ConfigLoader.cpp

    # Services
    src/services/QueueService.cpp
    src/services/RedisPublisher.cpp
    src/services/ValidationService.cpp
    src/services/TempFileService.cpp
)

# ==========================================
# Executable
# ==========================================

add_executable(video_processor_service
    ${VIDEO_PROCESSOR_SOURCES}
)

# ==========================================
# Include Directories
# ==========================================

target_include_directories(video_processor_service
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)

# ==========================================
# Link Libraries
# ==========================================

target_link_libraries(video_processor_service
    PRIVATE
        redis++::redis++
        Threads::Threads
)

# ==========================================
# Build Information
# ==========================================

message(STATUS "======================================")
message(STATUS "Video Processor Service Configuration")
message(STATUS "======================================")
message(STATUS "C++ Standard: ${CMAKE_CXX_STANDARD}")
message(STATUS "Compiler: ${CMAKE_CXX_COMPILER_ID}")
message(STATUS "Compiler Version: ${CMAKE_CXX_COMPILER_VERSION}")
message(STATUS "Build Type: ${CMAKE_BUILD_TYPE}")
message(STATUS "======================================")
