#include <iostream>
#include <string>
#include "gpu_adreno.h"

int main() {
    std::cout << "========================================\n";
    std::cout << "   FAH Adreno ARM64 WMI Test Tool       \n";
    std::cout << "========================================\n";

    fah::gpu::Adreno adreno;
    
    std::cout << "[*] Kører WMI-forespørgsel for at omgå PCI-detektion...\n";
    if (adreno.detect()) {
        std::cout << "\n[SUCCESS] Juhu! Adreno GPU blev fundet via WMI!\n";
        std::cout << "[*] GPU Navn: " << adreno.get_gpu_id() << "\n";
    } else {
        std::cout << "\n[WARNING] Adreno GPU blev ikke fundet via standard WMI klasser, men koden kørte!\n";
    }

    std::cout << "========================================\n";
    std::cout << "Tryk paa en tast for at afslutte...\n";
    std::cin.get();
    return 0;
}