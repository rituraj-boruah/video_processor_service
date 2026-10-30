#include "infra/FFmpegRunner.h"
#include "utils/CommandExecutor.h"

bool FFmpegRunner::encode(const std::string& input,
                          const std::string& output) {


    std::string cmd =
        "ffmpeg -y -i \"" + input + "\" "
        "-c:v libx265 -crf 28 -preset medium "
        "-c:a aac "
        "\"" + output + "\"";




    return CommandExecutor::run(cmd) == 0;

}
