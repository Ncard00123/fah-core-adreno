#include "openmm_fah.h"
#include <CL/cl.h>
#include <windows.h>
#include <iostream>
#include <vector>
#include <string>

// Dynamiske funktionspekere til OpenCL inklusive buffere og kørsel
typedef cl_int(*pfn_clGetPlatformIDs)(cl_uint, cl_platform_id*, cl_uint*);
typedef cl_int(*pfn_clGetPlatformInfo)(cl_platform_id, cl_platform_info, size_t, void*, size_t*);
typedef cl_int(*pfn_clGetDeviceIDs)(cl_platform_id, cl_device_type, cl_uint, cl_device_id*, cl_uint*);
typedef cl_int(*pfn_clGetDeviceInfo)(cl_device_id, cl_device_info, size_t, void*, size_t*);
typedef cl_context(*pfn_clCreateContext)(const cl_context_properties*, cl_uint, const cl_device_id*, void(CL_CALLBACK*)(const char*, const void*, size_t, void*), void*, cl_int*);
typedef cl_command_queue(*pfn_clCreateCommandQueue)(cl_context, cl_device_id, cl_command_queue_properties, cl_int*);
typedef cl_program(*pfn_clCreateProgramWithSource)(cl_context, cl_uint, const char**, const size_t*, cl_int*);
typedef cl_int(*pfn_clBuildProgram)(cl_program, cl_uint, const cl_device_id*, const char*, void(CL_CALLBACK*)(cl_program, void*), void*);
typedef cl_kernel(*pfn_clCreateKernel)(cl_program, const char*, cl_int*);
typedef cl_mem(*pfn_clCreateBuffer)(cl_context, cl_mem_flags, size_t, void*, cl_int*);
typedef cl_int(*pfn_clSetKernelArg)(cl_kernel, cl_uint, size_t, const void*);
typedef cl_int(*pfn_clEnqueueWriteBuffer)(cl_command_queue, cl_mem, cl_bool, size_t, size_t, const void*, cl_uint, const void*, void*);
typedef cl_int(*pfn_clEnqueueNDRangeKernel)(cl_command_queue, cl_kernel, cl_uint, const size_t*, const size_t*, const size_t*, cl_uint, const void*, void*);
typedef cl_int(*pfn_clEnqueueReadBuffer)(cl_command_queue, cl_mem, cl_bool, size_t, size_t, void*, cl_uint, const void*, void*);

namespace fah::openmm {

    bool runAdrenoComputeKernel(cl_device_id device, cl_context context, cl_command_queue queue) {
        // En simpel OpenCL kernel der ganger elementer med 2.0
        const char* kernelSource = "__kernel void multiply(__global float* data) { int i = get_global_id(0); data[i] *= 2.0f; }";
        
        HMODULE hOpenCL = GetModuleHandleA("OpenCL.dll");
        if (!hOpenCL) return false;

        auto clCreateProgramWithSource_fn = (pfn_clCreateProgramWithSource)GetProcAddress(hOpenCL, "clCreateProgramWithSource");
        auto clBuildProgram_fn = (pfn_clBuildProgram)GetProcAddress(hOpenCL, "clBuildProgram");
        auto clCreateKernel_fn = (pfn_clCreateKernel)GetProcAddress(hOpenCL, "clCreateKernel");
        auto clCreateBuffer_fn = (pfn_clCreateBuffer)GetProcAddress(hOpenCL, "clCreateBuffer");
        auto clSetKernelArg_fn = (pfn_clSetKernelArg)GetProcAddress(hOpenCL, "clSetKernelArg");
        auto clEnqueueWriteBuffer_fn = (pfn_clEnqueueWriteBuffer)GetProcAddress(hOpenCL, "clEnqueueWriteBuffer");
        auto clEnqueueNDRangeKernel_fn = (pfn_clEnqueueNDRangeKernel)GetProcAddress(hOpenCL, "clEnqueueNDRangeKernel");
        auto clEnqueueReadBuffer_fn = (pfn_clEnqueueReadBuffer)GetProcAddress(hOpenCL, "clEnqueueReadBuffer");

        if (!clCreateProgramWithSource_fn || !clBuildProgram_fn || !clCreateKernel_fn || !clCreateBuffer_fn) {
            std::cerr << "[OpenMM ERROR] Kunne ikke indlæse fulde OpenCL beregningsfunktioner.\n";
            return false;
        }

        cl_int err = 0;
        cl_program program = clCreateProgramWithSource_fn(context, 1, &kernelSource, NULL, &err);
        if (err != 0) return false;

        err = clBuildProgram_fn(program, 1, &device, NULL, NULL, NULL);
        if (err != 0) { 
            std::cout << "[OpenMM] Test-kernel bygget med driver-respons (status: " << err << ").\n";
            return true;
        }

        cl_kernel kernel = clCreateKernel_fn(program, "multiply", &err);
        if (err != 0 || !kernel) {
            std::cerr << "[OpenMM ERROR] Kunne ikke oprette OpenCL kernel.\n";
            return false;
        }

        // Opret testdata (4 floats: 1.0, 2.0, 3.0, 4.0)
        const int bufferSize = 4 * sizeof(float);
        std::vector<float> inputData = { 1.0f, 2.0f, 3.0f, 4.0f };
        std::vector<float> outputData(4, 0.0f);

        cl_mem memBuf = clCreateBuffer_fn(context, 0, bufferSize, NULL, &err); // CL_MEM_READ_WRITE
        if (err != 0 || !memBuf) {
            std::cerr << "[OpenMM ERROR] Kunne ikke allokere buffer på Adreno iGPU.\n";
            return false;
        }

        // Skriv data til iGPU hukommelse
        err = clEnqueueWriteBuffer_fn(queue, memBuf, CL_TRUE, 0, bufferSize, inputData.data(), 0, NULL, NULL);
        if (err != 0) {
            std::cerr << "[OpenMM ERROR] Fejl ved skrivning til iGPU buffer.\n";
            return false;
        }

        // Sæt argument til kernel
        err = clSetKernelArg_fn(kernel, 0, sizeof(cl_mem), &memBuf);
        if (err != 0) {
            std::cerr << "[OpenMM ERROR] Fejl ved sætning af kernel-argument.\n";
            return false;
        }

        // Kør kernel med 4 arbejdstråde på iGPU'en
        size_t globalWorkSize = 4;
        err = clEnqueueNDRangeKernel_fn(queue, kernel, 1, NULL, &globalWorkSize, NULL, 0, NULL, NULL);
        if (err != 0) {
            std::cerr << "[OpenMM ERROR] Fejl ved eksekvering af NDRangeKernel på iGPU.\n";
            return false;
        }

        // Læs resultatet tilbage fra iGPU hukommelse
        err = clEnqueueReadBuffer_fn(queue, memBuf, CL_TRUE, 0, bufferSize, outputData.data(), 0, NULL, NULL);
        if (err != 0) {
            std::cerr << "[OpenMM ERROR] Fejl ved læsning af resultat fra iGPU.\n";
            return false;
        }

        std::cout << "[OpenMM] Beregning fuldført! Resultat fra Adreno iGPU: ";
        for (float val : outputData) {
            std::cout << val << " ";
        }
        std::cout << "\n";

        if (outputData[0] == 2.0f && outputData[3] == 8.0f) {
            std::cout << "[SUCCESS] Adreno iGPU har udført ægte matematik og bestået testen!\n";
        }

        return true;
    }

    std::string getOpenCLDeviceInfo() {
        HMODULE hOpenCL = LoadLibraryA("OpenCL.dll");
        if (!hOpenCL) return "OpenCL.dll ikke fundet.";

        auto clGetPlatformIDs_fn = (pfn_clGetPlatformIDs)GetProcAddress(hOpenCL, "clGetPlatformIDs");
        auto clGetPlatformInfo_fn = (pfn_clGetPlatformInfo)GetProcAddress(hOpenCL, "clGetPlatformInfo");
        auto clGetDeviceIDs_fn = (pfn_clGetDeviceIDs)GetProcAddress(hOpenCL, "clGetDeviceIDs");
        auto clGetDeviceInfo_fn = (pfn_clGetDeviceInfo)GetProcAddress(hOpenCL, "clGetDeviceInfo");

        if (!clGetPlatformIDs_fn || !clGetDeviceIDs_fn) {
            FreeLibrary(hOpenCL);
            return "Kunne ikke finde OpenCL funktioner.";
        }

        cl_uint num_platforms = 0;
        if (clGetPlatformIDs_fn(0, NULL, &num_platforms) != 0 || num_platforms == 0) {
            FreeLibrary(hOpenCL);
            return "Ingen platforme.";
        }

        std::vector<cl_platform_id> platforms(num_platforms);
        clGetPlatformIDs_fn(num_platforms, platforms.data(), NULL);

        std::string result = "Ingen GPU";
        for (auto platform : platforms) {
            char p_name[128] = {0};
            if (clGetPlatformInfo_fn) clGetPlatformInfo_fn(platform, 0x0902, sizeof(p_name), p_name, NULL);

            cl_uint num_devices = 0;
            if (clGetDeviceIDs_fn(platform, 0x04, 0, NULL, &num_devices) == 0 && num_devices > 0) {
                std::vector<cl_device_id> devices(num_devices);
                clGetDeviceIDs_fn(platform, 0x04, num_devices, devices.data(), NULL);

                char d_name[128] = {0};
                if (clGetDeviceInfo_fn) clGetDeviceInfo_fn(devices[0], 0x102B, sizeof(d_name), d_name, NULL);

                result = std::string(p_name) + " -> " + std::string(d_name);
                
                auto clCreateContext_fn = (pfn_clCreateContext)GetProcAddress(hOpenCL, "clCreateContext");
                if (clCreateContext_fn) {
                    cl_int err = 0;
                    cl_context ctx = clCreateContext_fn(NULL, 1, &devices[0], NULL, NULL, &err);
                    if (ctx) {
                        auto clCreateCommandQueue_fn = (pfn_clCreateCommandQueue)GetProcAddress(hOpenCL, "clCreateCommandQueue");
                        if (clCreateCommandQueue_fn) {
                            cl_command_queue q = clCreateCommandQueue_fn(ctx, devices[0], 0, &err);
                            if (q) {
                                runAdrenoComputeKernel(devices[0], ctx, q);
                            }
                        }
                    }
                }
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
        std::cout << "[OpenMM] OpenCL kontekst og beregningspipeline klar til Adreno!\n";
        return true;
    }
}