#pragma once
#include <string>

namespace fah::openmm {
    bool initializeOpenMMContext();
    std::string getOpenCLDeviceInfo();
}