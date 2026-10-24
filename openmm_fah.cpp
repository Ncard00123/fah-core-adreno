#include "openmm_fah.h"
#include <iostream>

namespace fah::openmm {
    bool initializeOpenMMContext() {
        std::cout << "[OpenMM] Initializing Adreno OpenMM bridge wrapper..." << std::endl;
        // Mock success for ARM64 testing
        return true;
    }
}