#include <iostream>
#include <string>
#include "gpu_adreno.h"
#include "openmm_fah.h"

int main() {
    std::cout << "========================================\n";
    std::cout << "   FAH Adreno ARM64 Test Suite         \n";
    std::cout << "========================================\n";

    // 1. Test WMI GPU Detektion
    fah::gpu::Adreno adreno;
    std::cout << "[*] Kører WMI-forespørgsel for Adreno iGPU...\n";
    if (adreno.detect()) {
        std::cout << "[SUCCESS] GPU fundet: " << adreno.get_gpu_id() << "\n\n";
    } else {
        std::cout << "[WARNING] WMI kunne ikke finde GPU'en.\n\n";
    }

    // 2. Test OpenCL / OpenMM Broen
    std::cout << "[*] Tester OpenCL / OpenMM initialisering...\n";
    if (fah::openmm::initializeOpenMMContext()) {
        std::cout << "[SUCCESS] OpenMM OpenCL broen kører!\n";
    } else {
        std::cout << "[WARNING] OpenCL initialisering fejlede.\n";
    }

    std::cout << "========================================\n";
    std::cout << "Tryk på en tast for at afslutte...\n";
    std::cin.get();
    return 0;
}