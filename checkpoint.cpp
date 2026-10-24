#include <string>
#include <stdexcept>
#include <fstream>

class CheckpointHandler {
public:
    static void saveCheckpoint(int step, const std::string& filename) {
        std::ofstream outfile(filename, std::ios::binary);
        if (!outfile.is_open()) {
            throw std::runtime_error("Failed to open checkpoint file for writing.");
        }
        outfile.write(reinterpret_cast<const char*>(&step), sizeof(step));
    }

    static int loadCheckpoint(const std::string& filename) {
        std::ifstream infile(filename, std::ios::binary);
        if (!infile.is_open()) {
            throw std::runtime_error("Failed to open checkpoint file for reading.");
        }
        int step = 0;
        infile.read(reinterpret_cast<char*>(&step), sizeof(step));
        return step;
    }
};