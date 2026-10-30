#include "utils/PlaylistGenerator.h"
#include <fstream>

void generateMasterPlaylist(const std::string& baseOutput) {

    std::ofstream file(baseOutput + "/master.m3u8");

    file << "#EXTM3U\n";

    file << "#EXT-X-STREAM-INF:BANDWIDTH=4500000,RESOLUTION=1920x1080\n";
    file << "1080p/index.m3u8\n";

    file << "#EXT-X-STREAM-INF:BANDWIDTH=2500000,RESOLUTION=1280x720\n";
    file << "720p/index.m3u8\n";

    file << "#EXT-X-STREAM-INF:BANDWIDTH=1200000,RESOLUTION=854x480\n";
    file << "480p/index.m3u8\n";

    file.close();
}