#pragma once
#include <string>

namespace fah::checkpoint {
    bool saveCheckpoint(int step, const std::string& filename = "fah_checkpoint.dat");
    bool loadCheckpoint(int& step, const std::string& filename = "fah_checkpoint.dat");
}