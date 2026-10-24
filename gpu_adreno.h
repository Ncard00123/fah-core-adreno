#pragma once

#include <string>
#include <vector>
#include <windows.h>

namespace fah {
namespace gpu {

class Adreno {
public:
    Adreno();
    ~Adreno();

    // Detects Adreno GPU using Windows WMI and PnP APIs
    bool detect();

    // Returns GPU ID (e.g., "Adreno 660")
    std::string get_gpu_id() const noexcept {
        return m_gpu_id;
    }

    // Checks if GPU is available and ready for OpenCL/Vulkan/DirectML
    bool is_available() const noexcept {
        return m_is_available;
    }

    // Creates an OpenCL context for the Adreno GPU
    cl::Context create_opencl_context();

    // Creates a Vulkan instance for the Adreno GPU (if supported)
    VkInstance create_vulkan_instance() const;

    // Creates a DirectML device for the Adreno GPU (if supported)
    ID3D12Device* create_directml_device() const;

    // Updates GPU utilization visualization (0-100%)
    void update_gpu_utilization(int utilization);

    // Get GPU temperature in Celsius (-5 to 120 degrees)
    int get_gpu_temperature() const;

    // Check if GPU is throttling (due to temperature or power limits)
    bool is_throttled() const;its)
    bool is_throttling_active() const;

    // Get maximum supported temperature (for reference)
    int get_max_temperature() const;

    // Check if GPU is currently within safe temperature range (50-85°C)
    bool is_in_safe_range() const;

    // Check if GPU is in critical temperature state (>90°C)
    bool is_in_critical_state() const;

    // Check if GPU is in emergency state (>105°C)
    bool is_in_emergency_state() const;

private:
    std::string m_gpu_id;
    bool m_is_available;
    int m_gpu_utilization;  // Percentage (0-100)
    int m_gpu_temperature;   // Current temperature in Celsius
    bool m_throttling_active; // True if GPU is throttled
    int m_max_temperature;    // Maximum supported temperature by GPU

    // Windows-specific GPU detection helpers
    bool query_wmi_classes();
    bool query_pnp_entities();
    bool is_adreno_gpu(const std::wstring& name) const;
    size_t get_gpu_memory_kb() const;

    // GPU context management
    cl::Context m_opencl_context;
    VkInstance m_vulkan_instance;
    ID3D12Device* m_directml_device;

    // OpenCL configuration tuning
    size_t get_workgroup_size() const;
    size_t get_max_workgroup_size() const;
    void tune_workgroup_sizes(const cl::Context& context);
    void detect_gpu_memory();

    // Progress bar and GPU visualization
    std::ostream* m_progress_bar;
    void initialize();e_progress_bar();
    void update_progress_bar(int progress);
};

} // namespace gpu
} // namespace fah
