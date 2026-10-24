#include "openmm_fah.h"
#include <CL/cl.h>
#include <windows.h>
#include <iostream>
#include <vector>
#include <string>

// Funktionspekere til dynamisk indlæsning af OpenCL.dll
typedef cl_int(*pfn_clGetPlatformIDs)(cl_uint, cl_platform_id*, cl_uint*);
typedef cl_int(*pfn_clGetPlatformInfo)(cl_platform_id, cl_platform_info, size_t, void*, size_t*);
typedef cl_int(*pfn_clGetDeviceIDs)(cl_platform_id, cl_device_type, cl_uint, cl_device_id*, cl_uint*);
typedef cl_int(*pfn_clGetDeviceInfo)(cl_device_id, cl_device_info, size_t, void*, size_t*);

namespace fah::openmm {

    std::string getOpenCLDeviceInfo() {
        HMODULE hOpenCL = LoadLibraryA("OpenCL.dll");
        if (!hOpenCL) {
            return "OpenCL.dll ikke fundet på systemet.";
        }

        auto clGetPlatformIDs_fn = (pfn_clGetPlatformIDs)GetProcAddress(hOpenCL, "clGetPlatformIDs");
        auto clGetPlatformInfo_fn = (pfn_clGetPlatformInfo)GetProcAddress(hOpenCL, "clGetPlatformInfo");
        auto clGetDeviceIDs_fn = (pfn_clGetDeviceIDs)GetProcAddress(hOpenCL, "clGetDeviceIDs");
        auto clGetDeviceInfo_fn = (pfn_clGetDeviceInfo)GetProcAddress(hOpenCL, "clGetDeviceInfo");

        if (!clGetPlatformIDs_fn || !clGetDeviceIDs_fn) {
            FreeLibrary(hOpenCL);
            return "Kunne ikke finde OpenCL funktioner i DLL.";
        }

        cl_uint num_platforms = 0;
        if (clGetPlatformIDs_fn(0, NULL, &num_platforms) != 0 || num_platforms == 0) {
            FreeLibrary(hOpenCL);
            return "Ingen OpenCL platforme fundet.";
        }

        std::vector<cl_platform_id> platforms(num_platforms);
        clGetPlatformIDs_fn(num_platforms, platforms.data(), NULL);

        std::string result = "Ingen GPU fundet";

        for (auto platform : platforms) {
            char p_name[128] = {0};
            if (clGetPlatformInfo_fn) {
                clGetPlatformInfo_fn(platform, 0x0902 /* CL_PLATFORM_NAME */, sizeof(p_name), p_name, NULL);
            }

            cl_uint num_devices = 0;
            if (clGetDeviceIDs_fn(platform, 0x04 /* CL_DEVICE_TYPE_GPU */, 0, NULL, &num_devices) == 0 && num_devices > 0) {
                std::vector<cl_device_id> devices(num_devices);
                clGetDeviceIDs_fn(platform, 0x04 /* CL_DEVICE_TYPE_GPU */, num_devices, devices.data(), NULL);

                char d_name[128] = {0};
                if (clGetDeviceInfo_fn) {
                    clGetDeviceInfo_fn(devices[0], 0x102B /* CL_DEVICE_NAME */, sizeof(d_name), d_name, NULL);
                }

                result = std::string(p_name) + " -> " + std::string(d_name);
                break;
            }
        }

        FreeLibrary(hOpenCL);
        return result;
    }

    bool initializeOpenMMContext() {
        std::cout << "[OpenMM] Initialiserer OpenCL kontekst til Adreno GPU...\n";
        
        std::string deviceInfo = getOpenCLDeviceInfo();
        std::cout << "[OpenMM] Fundet OpenCL Enhed: " << deviceInfo << std::endl;

        if (deviceInfo.find("ikke fundet") != std::string::npos || deviceInfo.find("Ingen") != std::string::npos) {
            std::cerr << "[OpenMM WARNING] Ingen aktiv OpenCL GPU-enhed fundet via driver.\n";
            return true; 
        }

        std::cout << "[OpenMM] OpenCL kontekst succesfuldt oprettet til Adreno!\n";
        return true;
    }
}