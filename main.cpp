#include <iostream>
#include <string>
#include "gpu_adreno.h"
#include "openmm_fah.h"
#include "checkpoint.h"

int main(int argc, char* argv[]) {
    std::cout << "========================================\n";
    std::cout << "   FAH Adreno ARM64 Core Bridge        \n";
    std::cout << "========================================\n";

    // Udskriv eventuelle argumenter sendt fra F@h klienten
    if (argc > 1) {
        std::cout << "[*] Modtog " << (argc - 1) << " argument(er) fra klienten:\n";
        for (int i = 1; i < argc; ++i) {
            std::cout << "    - Arg " << i << ": " << argv[i] << "\n";
        }
    } else {
        std::cout << "[*] Ingen ekstra argumenter fundet (kører i standard test-tilstand).\n";
    }
    std::cout << "\n";

    // 1. WMI GPU Detektion
    fah::gpu::Adreno adreno;
    std::cout << "[*] Kører WMI-forespørgsel for Adreno iGPU...\n";
    if (adreno.detect()) {
        std::cout << "[SUCCESS] GPU fundet: " << adreno.get_gpu_id() << "\n\n";
    } else {
        std::cout << "[WARNING] WMI kunne ikke finde GPU'en.\n\n";
    }

    // 2. Checkpoint System
    int currentStep = 0;
    fah::checkpoint::loadCheckpoint(currentStep);
    currentStep += 100; 
    fah::checkpoint::saveCheckpoint(currentStep);
    std::cout << "\n";

    // 3. OpenCL / OpenMM & Adreno Matematik
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