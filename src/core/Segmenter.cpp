#include "core/Segmenter.h"
#include "utils/CommandExecutor.h"

bool Segmenter::segment(const std::string& input,
                        const std::string& outputDir) {

    std::string cmd =
    "ffmpeg -y -i \"" + input + "\" "
    "-c:v copy -c:a copy "
    "-f hls "
    "-hls_time 10 "
    "-hls_list_size 0 "
    "-hls_segment_filename \"" + outputDir + "/seg_%03d.ts\" "
    "\"" + outputDir + "/index.m3u8\"";

    return CommandExecutor::run(cmd) == 0;
}