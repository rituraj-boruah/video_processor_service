cmake_minimum_required(VERSION 3.22)

project(video_processor_service)

set(CMAKE_CXX_STANDARD 20)

include_directories(include)
include_directories(/ucrt64/include)

link_directories(/ucrt64/lib)

add_executable(video_processor_service
        src/main.cpp

        src/core/Encoder.cpp
        src/core/Segmenter.cpp
        src/core/Pipeline.cpp
        src/core/MetadataGenerator.cpp

        src/infra/FFmpegRunner.cpp
        src/infra/FFprobeRunner.cpp

        src/utils/CommandExecutor.cpp
        src/utils/PlaylistGenerator.cpp

        src/config/ConfigLoader.cpp

        src/services/QueueService.cpp
        src/services/RedisPublisher.cpp
        src/services/ValidationService.cpp
        src/services/TempFileService.cpp
)

target_link_libraries(video_processor_service
        redis++
        hiredis
)