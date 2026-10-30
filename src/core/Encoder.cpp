#include "core/Encoder.h"
#include "utils/CommandExecutor.h"

bool Encoder::encodeMultiple(const std::string& input,
                             const std::string& baseOutput) {

    std::string cmd =
        "ffmpeg -y -i \"" + input + "\" "
        "-filter_complex \""
        "[0:v]split=3[v1][v2][v3];"
        "[v1]scale=1920:1080[v1out];"
        "[v2]scale=1280:720[v2out];"
        "[v3]scale=854:480[v3out]"
        "\" "
        "-map \"[v1out]\" -c:v:0 libx265 -crf 28 -preset fast "
        "-map \"[v2out]\" -c:v:1 libx265 -crf 30 -preset fast "
        "-map \"[v3out]\" -c:v:2 libx265 -crf 32 -preset fast "
        "-map a:0 -c:a aac "
        "-f tee \""
        "[f=mp4]" + baseOutput + "/1080p/master.mp4|"
        "[f=mp4]" + baseOutput + "/720p/master.mp4|"
        "[f=mp4]" + baseOutput + "/480p/master.mp4"
        "\"";

    return CommandExecutor::run(cmd) == 0;
}