cmake_minimum_required(VERSION 3.20)
project(fah-core-adreno LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Enable MSVC ARM64
if(CMAKE_CXX_COMPILER_ID MATCHES "MSVC")
    add_compile_options(/W4 /WX- /utf-8)
    add_definitions(-DFAH_PLATFORM_WINDOWS)
else()
    message(FATAL_ERROR "Unsupported compiler for ARM64")
endif()

# Hent OpenCL Headers automatisk fra Khronos Group
include(FetchContent)
FetchContent_Declare(
    OpenCLHeaders
    GIT_REPOSITORY https://github.com/KhronosGroup/OpenCL-Headers.git
    GIT_TAG v2024.05.08
)
FetchContent_MakeAvailable(OpenCLHeaders)

# Opret OpenCL target
add_library(OpenCL::OpenCL INTERFACE IMPORTED)
target_include_directories(OpenCL::OpenCL INTERFACE ${openclheaders_SOURCE_DIR})

# GPU Adreno bibliotek (inklusiv WMI links)
add_library(gpu_adreno STATIC gpu_adreno.cpp gpu_adreno.h)
target_include_directories(gpu_adreno PUBLIC 
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${openclheaders_SOURCE_DIR}
)
target_link_libraries(gpu_adreno PRIVATE ole32.lib user32.lib wbemuuid.lib)
target_compile_definitions(gpu_adreno PRIVATE -DFAH_PLATFORM_WINDOWS)

# OpenMM integration (bruger dynamisk indlæsning af OpenCL.dll)
add_library(openmm_fah STATIC openmm_fah.cpp openmm_fah.h)
target_include_directories(openmm_fah PUBLIC 
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${openclheaders_SOURCE_DIR}
)
target_link_libraries(openmm_fah PRIVATE gpu_adreno)

# Checkpoint handling
add_library(checkpoint STATIC checkpoint.cpp)
target_include_directories(checkpoint PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

# Opret en kørbar test-fil
add_executable(fah-test main.cpp)
target_link_libraries(fah-test PRIVATE gpu_adreno openmm_fah checkpoint)
