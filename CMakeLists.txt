cmake_minimum_required(VERSION 3.20)

project(fah-core-adreno LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Enable MSVC/Clang ARM64
if(CMAKE_CXX_COMPILER_ID MATCHES "MSVC")
    add_compile_options(/arch:ARM64 /W4 /WX /analyze)
    add_definitions(-DFAH_PLATFORM_WINDOWS)
elseif(CMAKE_CXX_COMPILER_ID MATCHES "Clang")
    add_compile_options(-mcpu=armv8-a -O3 -Wall -Wextra)
    add_definitions(-DFAH_PLATFORM_WINDOWS)
else()
    message(FATAL_ERROR "Unsupported compiler for ARM64")
endif()

# Dependencies
find_package(OpenCL REQUIRED)
find_package(OpenMPI REQUIRED)

if(OpenCL_FOUND)
    target_link_libraries(gpu_adreno PRIVATE ${OpenCL_LIBRARIES})
endif()

if(Vulkan_FOUND)
    target_link_libraries(gpu_adreno PRIVATE ${Vulkan_LIBRARIES})
    add_compile_options(-DVULKAN_ENABLE_DEVICE_DISCOVERY)
endif()
=======

# Windows-specific libraries
find_package(WMI REQUIRED)
find_package(COMCommon REQUIRED)

if(MSVC)
    add_library(wmi_com STATIC)
    target_link_libraries(wmi_com PRIVATE ole32.lib user32.lib)
    add_compile_options(/WX)
    add_definitions(-DFAH_PLATFORM_WINDOWS)
elseif(Clang)
    target_link_libraries(wmi_com PRIVATE -lole32 -luser32)
    add_compile_options(-Werror)
    add_definitions(-DFAH_PLATFORM_WINDOWS)
endif()

# GPU Adreno modules
add_library(gpu_adreno STATIC gpu_adreno.cpp gpu_adreno.h)
target_include_directories(gpu_adreno PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
)
=======

# GPU Adreno modules
add_library(gpu_adreno STATIC gpu_adreno.cpp gpu_adreno.h)
target_include_directories(gpu_adreno PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
)

# OpenMM integration
add_library(openmm_fah STATIC openmm_fah.cpp openmm_fah.h)
target_link_libraries(openmm_fah PRIVATE
    gpu_adreno
    OpenCL::OpenCL
    wmi_com
    OpenMPI::MPI_CXX
    Vulkan::Vulkan
    OpenMM::OpenMM
)

# Checkpoint handling
add_library(checkpoint STATIC checkpoint.cpp)
target_include_directories(checkpoint PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>)

# Main core
add_executable(fah-core-adreno
    gpu_adreno.cpp
    openmm_fah.cpp
    checkpoint.cpp
    main.cpp
)

target_link_libraries(fah-core-adreno PRIVATE
    gpu_adreno
    openmm_fah
    checkpoint
    OpenCL::OpenCL
    OpenMPI::MPI_CXX
    Vulkan::Vulkan)

# Install
install(TARGETS fah-core-adreno
    ARCHIVE
    LIBRARY
    RUNTIME
    DESTINATION bin)

install(DIRECTORY include/ DESTINATION include)
install(FILES gpu_adreno.dll DESTINATION bin)  # Explicitly install DLLs
