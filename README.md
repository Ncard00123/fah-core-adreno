\# FAH Adreno ARM64 Core Bridge



An experimental project designed to integrate the Qualcomm Adreno iGPU (Snapdragon X2-90) into the Folding@home ecosystem on Windows ARM64 platforms\[cite: 1].



\## Features

\- \*\*WMI Hardware Wrapper:\*\* Bypasses standard hardware detection to properly identify Qualcomm Adreno iGPUs on Windows ARM64\[cite: 1].

\- \*\*Dynamic OpenCL Loader:\*\* Resolves ARM64 linker issues by dynamically loading `OpenCL.dll` and validating compute capabilities.

\- \*\*Persistent Checkpointing:\*\* Tracks and increments simulation steps across sessions to ensure seamless operation.

\- \*\*Modular Test Suite:\*\* Includes command-line argument parsing to simulate a real F@h client invocation.



\## Build Instructions (Windows ARM64)

1\. Ensure you have Visual Studio installed with C++ and ARM64 build tools.

2\. Open a developer PowerShell, create a build directory, and configure via CMake:

&#x20;  ```powershell

&#x20;  mkdir build

&#x20;  cd build

&#x20;  cmake -A ARM64 ..

