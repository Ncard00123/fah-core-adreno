#pragma once

#include <fstream>
#include <vector>
#include <cstring>
#include <iostream>
#include <stdexcept>
#include <algorithm>
#include <cstdint>  // For uint32_t
#include <cmath>    // For std::isnan, std::isinf

namespace fah {
namespace checkpoint {

/**
 * @class CheckpointManager
 * @brief Handles serialization and deserialization of single-precision simulation state.
 */
class CheckpointManager {
public:
    CheckpointManager() = default;
    ~CheckpointManager() = default;

    /**
     * @brief Serializes a float32 array to a binary file.
     * @param data Pointer to the float32 array.
     * @param size Number of elements in the array.
     * @param filename Path to the output file.
     * @throws std::runtime_error if serialization fails.
     */
    static void serialize_float32(const float* data, size_t size, const std::string& filename) {
        if (data == nullptr || size == 0) {
            throw std::runtime_error("Invalid data or size for serialization");
        }

        std::ofstream outFile(filename, std::ios::binary);
        if (!outFile.is_open()) {
            throw std::runtime_error("Failed to open file for serialization: " + filename);
        }

        // Write size first (as uint32_t)
        uint32_t array_size = static_cast<uint32_t>(size);
        if (!outFile.write(reinterpret_cast<const char*>(&array_size), sizeof(array_size))) {
            throw std::runtime_error("Failed to write size to file");
        }

        // Write data
        if (!outFile.write(reinterpret_cast<const char*>(data), size * sizeof(float))) {
            throw std::runtime_error("Failed to write data to file");
        }
    }

    /**
     * @brief Deserializes a binary file into a float32 vector.
     * @param filename Path to the input file.
     * @param data Reference to vector to store deserialized data.
     * @throws std::runtime_error if deserialization fails.
     */
    static void deserialize_float32(const std::string& filename, std::vector<float>& data) {
        std::ifstream inFile(filename, std::ios::binary);
        if (!inFile.is_open()) {
            throw std::runtime_error("Failed to open file for deserialization: " + filename);
        }

        uint32_t size = 0;
        if (!inFile.read(reinterpret_cast<char*>(&size), sizeof(size))) {
            throw std::runtime_error("Failed to read size from file");
        }

        data.resize(size);
        if (!inFile.read(reinterpret_cast<char*>(data.data()), size * sizeof(float))) {
            throw std::runtime_error("Failed to read data from file");
        }
    }

    /**
     * @brief Checks if the file exists and is accessible.
     * @param filename Path to the file.
     * @return true if the file exists and is accessible, false otherwise.
     */
    static bool file_exists(const std::string& filename) {
        std::ifstream file(filename);
        return file.good();
    }

    /**
     * @brief Validates that a single-precision float array is well-formed.
     * @param data Pointer to the float32 array.
     * @param size Number of elements in the array.
     * @throws std::runtime_error if the data is invalid.
     */
    static void validate_float32(const float* data, size_t size) {
        if (data == nullptr || size == 0) {
            throw std::runtime_error("Invalid float32 array: null pointer or zero size");
        }

        // Check for NaN or infinity in the array
        for (size_t i = 0; i < size; ++i) {
            if (std::isnan(data[i]) || std::isinf(data[i])) {
                throw std::runtime_error("Invalid float32 value: NaN or infinity detected at index " + std::to_string(i));
            }
        }
    }
};

} // namespace checkpoint
} // namespace fah