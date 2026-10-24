#include "checkpoint.h"
#include <fstream>
#include <iostream>

namespace fah::checkpoint {

    bool saveCheckpoint(int step, const std::string& filename) {
        std::ofstream file(filename, std::ios::binary);
        if (!file.is_open()) {
            std::cerr << "[Checkpoint] Kunne ikke åbne fil til lagring: " << filename << "\n";
            return false;
        }
        file.write(reinterpret_cast<const char*>(&step), sizeof(step));
        std::cout << "[Checkpoint] Status gemt succesfuldt for trin: " << step << "\n";
        return true;
    }

    bool loadCheckpoint(int& step, const std::string& filename) {
        std::ifstream file(filename, std::ios::binary);
        if (!file.is_open()) {
            std::cout << "[Checkpoint] Ingen tidligere checkpoint-fil fundet. Starter fra trin 0.\n";
            step = 0;
            return false;
        }
        file.read(reinterpret_cast<char*>(&step), sizeof(step));
        std::cout << "[Checkpoint] Checkpoint indlæst! Genoptager fra trin: " << step << "\n";
        return true;
    }
}