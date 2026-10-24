#include <openmm/PlatformData.h>
#include <openmm/PlatformUtils.h>
#include <openmm/PlatformApplication.h>
#include <openmm/PlatformApplicationData.h>
#include <openmm/Context.h>
#include <openmm/Force.h>
#include <openmm/Platform.h>
#include <openmm/autoalign/autoalign_wrap_wrap_parm.h>
#include <openmm/autoalign/autoalign_wrap_wrap_topology.h>
#include <openmm/autoalign/autoalign_wrap_wrap_utils.h>
#include <openmm/autoalign/autoalign_wrap_wrap.h>
#include <openmm/autoalign/autoalign.h>
#include <openmm/autoalign/autoalign_parm.h>
#include <openmm/autoalign/autoalign_plugins.h>
#include <openmm/autoalign/autoalign_topology.h>
#include <openmm/autoalign/autoalign_utils.h>

#include <CL/cl.h>
#include <vulkan/vulkan.h>
#include <d3d12.h>
#include <d3d12shader.h>
#include <dxc/dxcompiler.h>
#include <dxc/dxil.h>

#include <gpu_adreno.h>
=======n.h>
#include <openmm/autoalign/autoalign_visualization_plugins.h>
#include <openmm/autoalign/autoalign_wrap.h>
#include <openmm/autoalign/autoalign_wrap_parm.h>
#include <openmm/autoalign/autoalign_wrap_topology.h>
#include <openmm/autoalign/autoalign_wrap_utils.h>
#include <openmm/autoalign/autoalign_wrap_visualization.h>
#include <openmm/autoalign/autoalign_wrap_visualization_plugins.h>
#include <openmm/autoalign/autoalign_wrap_wrap_visualization_plugins.h>
#include <openmm/autoalign/autoalign_wrap_wrap_wrap.h>
#include <openmm/autoalign/autoalign_wrap_wrap_wrap_parm.h>
#include <openmm/autoalign/autoalign_wrap_wrap_wrap_topology.h>
#include <openmm/autoalign/autoalign_wrap_wrap_wrap_utils.h>
#include <openmm/autoalign/autoalign_wrap_wrap_wrap_visualization.h>
#include <openmm/autoalign/autoalign_wrap_wrap_wrap_visualization_plugins.h>
#include <openmm/autoalign/autoalign_wrap_wrap_wrap_wrap.h>
#include <openmm/autoalign/autoalign_wrap_wrap_wrap_wrap_parm.h>
#include <openmm/autoalign/autoalign_wrap_wrap_wrap_wrap_topology.h>
#include <openmm/autoalign/autoalign_wrap_wrap_wrap_wrap_utils.h>
#include <openmm/autoalign/autoalign_wrap_wrap_wrap_wrap_visualization.h>
#include <openmm/autoalign/autoalign_wrap_wrap_wrap_wrap_visualization_plugins.h>
#include <openmm/autoalign/autoalign_wrap_wrap_wrap_wrap_wrap.h>
#include <openmm/autoalign/autoalign_wrap_wrap_wrap_wrap_wrap_parm.h>
#include <openmm/autoalign/autoalign_wrap_wrap_wrap_wrap_wrap_topology.h>
#include <openmm/autoalign/autoalign_wrap_wrap_wrap_wrap_wrap_utils.h>
#include <openmm/autoalign/autoalign_wrap_wrap_wrap_wrap_wrap_visualization.h>
#include <openmm/autoalign/autoalign_wrap_wrap_wrap_wrap_wrap_visualization_plugins.h>
#include <openmm/autoalign/autoalign_wrap_wrap_wrap_wrap_wrap_wrap.h>
#include <openmm/autoalign/autoalign_wrap_wrap_wrap_wrap_wrap_wrap_parm.h>
#include <openmm/autoalign/autoalign_wrap_wrap_wrap_wrap_wrap_wrap_topology.h>
#include <openmm/autoalign/autoalign_wrap_wrap_wrap_wrap_wrap_wrap_utils.h>
#include <openmm/autoalign/autoalign_wrap_wrap_wrap_wrap_wrap_wrap_visualization.h>
#include <openmm/autoalign/autoalign_wrap_wrap_wrap_wrap_wrap_wrap_visualization_plugins.h>
#include <openmm/autoalign/autoalign_wrap_wrap_wrap_wrap_wrap_wrap_wrap.h>
#include <openmm/autoalign/autoalign_wrap_wrap_wrap_wrap_wrap_wrap_wrap_parm.h>
#include <openmm/autoalign/autoalign_wrap_wrap_wrap_wrap_wrap_wrap_wrap_topology.h>
#include <openmm/autoalign/autoalign_wrap_wrap_wrap_wrap_wrap_wrap_wrap_utils.h>
#include <openmm/autoalign/autoalign_wrap_wrap_wrap_wrap_wrap_wrap_wrap_visualization.h>
#include <openmm/autoalign/autoalign_wrap_wrap_wrap_wrap_wrap_wrap_wrap_visualization_plugins.h>
#include <openmm/autoalign/autoalign_wrap_wrap_wrap_wrap_wrap_wrap_wrap_wrap.h>
#include <openmm/autoalign/autoalign_wrap_wrap_wrap_wrap_wrap_wrap_wrap_wrap_parm.h>
#include <openmm/autoalign/autoalign_wrap_wrap_wrap_wrap_wrap_wrap_wrap_wrap_topology.h>
#include <openmm/autoalign/autoalign_wrap_wrap_wrap_wrap_wrap_wrap_wrap_wrap_utils.h>
#include <openmm/autoalign/autoalign_wrap_wrap_wrap_wrap_wrap_wrap_wrap_wrap_visualization.h>
#include <openmm/autoalign/autoalign_wrap_wrap_wrap_wrap_wrap_wrap_wrap_wrap_visualization_plugins.h>
#include <openmm/autoalign/autoalign_wrap_wrap_wrap_wrap_wrap_wrap_wrap_wrap_wrap.h>
#include <openmm/autoalign/autoalign_wrap_wrap_wrap_wrap_wrap_wrap_wrap_wrap_wrap_parm.h>
#include <openmm/autoalign/autoalign_wrap_wrap_wrap_wrap_wrap_wrap_wrap_wrap_wrap_topology.h>
#include <openmm/autoalign/autoalign_wrap_wrap_wrap_wrap_wrap_wrap_wrap_wrap_wrap_utils.h>
#include <openmm/autoalign/autoalign_wrap_wrap_wrap_wrap_wrap_wrap_wrap_wrap_wrap_visualization.h>
#include <openmm/autoalign/autoalign_wrap_wrap_wrap_wrap_wrap_wrap_wrap_wrap_wrap_visualization_plugins.h>
#include <openmm/autoalign/autoalign_wrap_wrap_wrap_wrap_wrap_wrap_wrap_wrap_wrap_wrap.h>
#include <openmm/autoalign/autoalign_wrap_wrap_wrap_wrap_wrap_wrap_wrap_wrap_wrap_wrap_parm.h>
#include <openmm/autoalign/autoalign_wrap_wrap_wrap_wrap_wrap_wrap_wrap_wrap_wrap_wrap_topology.h>
#include <openmm/autoalign/autoalign_wrap_wrap_wrap_wrap_wrap_wrap_wrap_wrap_wrap_wrap_utils.h>
#include <openmm/autoalign/autoalign_wrap_wrap_wrap_wrap_wrap_wrap_wrap_wrap_wrap_wrap_visualization.h>
#include <openmm/autoalign/autoalign_wrap_wrap_wrap_wrap_wrap_wrap_wrap_wrap_wrap_wrap_visualization_plugins.h>
#include <openmm/autoalign/autoalign_wrap_wrap_wrap_wrap_wrap_wrap_wrap_wrap_wrap_wrap_wrap.h>
#include <openmm/autoalign/autoalign_wrap_wrap_wrap_wrap_wrap_wrap_wrap_wrap_wrap_wrap_wrap_parm.h>
#include <openmm/autoalign/autoalign_wrap_wrap_wrap_wrap_wrap_wrap_wrap_wrap_wrap_wrap_wrap_topology.h>
#include <openmm/autoalign/autoalign_wrap_wrap_wrap_wrap_wrap_wrap_wrap_wrap_wrap_wrap_wrap_utils.h>
#include <openmm/autoalign/autoalign_wrap_wrap_wrap_wrap_wrap_wrap_wrap_wrap_wrap_wrap_wrap_visualization.h>
#include <openmm/autoalign/autoalign_wrap_wrap_wrap_wrap_wrap_wrap_wrap_wrap_wrap_wrap_wrap_visualization_plugins.h>
#include <openmm/autoalign/autoalign_wrap_wrap_wrap_wrap_wrap_wrap_wrap_wrap_wrap_wrap_wrap_wrap.h>
#include <openmm/autoalign/autoalign_wrap_wrap_wrap_wrap_wrap_wrap_wrap_wrap_wrap_wrap_wrap_wrap_parm.h>
#include <openmm/autoalign/autoalign_wrap_wrap_wrap_wrap_wrap_wrap_wrap_wrap_wrap_wrap_wrap_wrap_topology.h>
#include <openmm/autoalign/autoalign_wrap_wrap_wrap_wrap_wrap_wrap_wrap_wrap_wrap_wrap_wrap_wrap_utils.h>
#include <openmm/autoalign/autoalign_wrap_wrap_wrap_wrap_wrap_wrap_wrap_wrap_wrap_wrap_wrap_wrap_visualization.h>
#include <openmm/autoalign/autoalign_wrap_wrap_wrap_wrap_wrap_wrap_wrap_wrap_wrap_wrap_wrap_wrap_visualization_plugins.h>
#include <openmm/autoalign/autoalign_wrap_wrap_wrap_wrap_wrap_wrap_wrap_wrap_wrap_wrap_wrap_wrap_wrap.h>
#include <openmm/autoalign/autoalign_wrap_wrap_wrap_wrap_wrap_wrap_wrap_wrap_wrap_wrap_wrap_wrap_wrap_parm.h>
#include <openmm/autoalign/autoalign_wrap_wrap_wrap_wrap_wrap_wrap_wrap_wrap_wrap_wrap_wrap_wrap_wrap_topology.h>
#include <openmm/autoalign/autoalign_wrap_wrap_wrap_wrap_wrap_wrap_wrap_wrap_wrap_wrap_wrap_wrap_wrap_utils.h>
#include <openmm/autoalign/autoalign_wrap_wrap_wrap_wrap_wrap_wrap_wrap_wrap_wrap_wrap_wrap_wrap_wrap_visualization.h>
#include <openmm/autoalign/autoalign_wrap_wrap_wrap_wrap_wrap_wrap_wrap_wrap_wrap_wrap_wrap_wrap_wrap_visualization_plugins.h>
#include <openmm/autoalign/autoalign_wrap_wrap_wrap_wrap_wrap_wrap_wrap_wrap_wrap_wrap_wrap_wrap_wrap_wrap.h>
#include <openmm/autoalign/autoalign_wrap_wrap_wrap_wrap_wwrap_wrap_wwrap_wwrap_wwrap_wwrap_wwrap_wwrap.h>

#include "gpu_adreno.h"
#include "checkpoint.h"

namespace fah {
namespace openmm {

class FAHCore {
public:
    FAHCore() : m_simulator(nullptr), m_gpu_adreno(nullptr), m_checkpoint(nullptr), m_workgroup_size(0), m_max_workgroup_size(0),
               m_temperature_monitor(nullptr) {}

    ~FAHCore() {
        if (m_simulator) {
            delete m_simulator;
        }
        if (m_gpu_adreno) {
            delete m_gpu_adreno;
        }
        if (m_checkpoint) {
            delete m_checkpoint;
        }
        if (m_temperature_monitor) {
            delete m_temperature_monitor;
        }
    }

    bool initialize(const std::vector<std::string>& args) {
        // Parse FAH arguments
        for (const auto& arg : args) {
            if (arg == "-gpu-platform" || arg == "-gpu-vendor") {
                // Handle GPU platform and vendor
                m_gpu_platform = arg;
            } else if (arg == "opencl" || arg == "qualcomm") {
                m_gpu_vendor = arg;
            }
        }

        // Initialize Adreno GPU detection
        m_gpu_adreno = new gpu::Adreno();
        if (!m_gpu_adreno->detect()) {
            std::cerr << "Error: Adreno GPU not detected or available." << std::endl;
            return false;
        }

        // Create OpenCL context for Adreno with adaptive workgroup tuning
        try {
            m_opencl_context = m_gpu_adreno->create_opencl_context();
        } catch (const std::exception& e) {
            std::cerr << "Error creating OpenCL context: " << e.what() << std::endl;
            return false;
        }

        // Initialize performance metrics
        // Get adaptive workgroup size from GPU
        m_workgroup_size = m_gpu_adreno->get_workgroup_size();
        m_max_workgroup_size = m_gpu_adreno->get_max_workgroup_size();

        // Initialize temperature monitoring thread
        m_temperature_monitor = new TemperatureMonitor(m_gpu_adreno);
        m_temperature_monitor->start();

        // Initialize other system monitoring
        m_simulator = new SimulationManager(m_opencl_context, m_workgroup_size, m_max_workgroup_size);kgroup_size = m_gpu_adreno->get_workgroup_size();
        m_max_workgroup_size = m_gpu_adreno->get_max_workgroup_size();
        m_gpu_adreno->tune_workgroup_sizes(m_opencl_context);

        // Start with 0% GPU utilization and update it during computation
        m_gpu_utilization = 0;

    private:
        // GPU utilization tracking
        int m_gpu_utilization;
        size_t m_workgroup_size;
        size_t m_max_workgroup_size;

        // Update GPU utilization visualization (called during computation)
        void update_gpu_utilization() {
            // Simplified GPU utilization - in a real implementation, this would be monitored
            // by querying GPU metrics or using OpenCL events
            // For now, we'll simulate it by increasing gradually
            m_gpu_utilization = (m_gpu_utilization + 1) % 101;
            m_gpu_adreno->update_gpu_utilization(m_gpu_utilization);
        }
};

} // namespace fah::openmm_size();
        std::cout << "Using adaptive workgroup size: " << workgroup_size << std::endl;
        m_fps = 0;
        m_gpu_load = 0.0f;
        m_workload_distribution.clear();
        m_workload_distribution.reserve(10); // Reserve space for 10 measurements

        // Initialize checkpoint handling
        m_checkpoint = new Checkpoint();
        if (!m_checkpoint->initialize()) {
            std::cerr << "Error initializing checkpoint"
            return false;
        }

        // Initialize OpenMM simulator
        try {
            m_simulator = new openmm::Simulator(
                m_opencl_context,
                openmm::Platform::getPlatformByName("CUDA"), // Placeholder, will be replaced
                1.0, // Force single precision
                openmm::ContextOptions()
            );
        } catch (const std::exception& e) {
            std::cerr << "Error initializing OpenMM simulator: " << e.what() << std::endl;
            return false;
        }

        return true;
    }

    bool run_simulation() {
        if (!m_simulator) {
            std::cerr << "Error: Simulator not initialized." << std::endl;
            return false;
        }

        try {
            m_simulator->run();
        } catch (const std::exception& e) {
            std::cerr << "Error running simulation: " << e.what() << std::endl;
            return false;
        }

        return true;
    }

    bool save_checkpoint() {
        if (!m_checkpoint) {
            std::cerr << "Error: Checkpoint not initialized." << std::endl;
            return false;
        }

        try {
            return m_checkpoint->save();
        } catch (const std::exception& e) {
            std::cerr << "Error saving checkpoint: " << e.what() << std::endl;
            return false;
        }
    }

    bool load_checkpoint() {
        if (!m_checkpoint) {
            std::cerr << "Error: Checkpoint not initialized." << std::endl;
            return false;
        }

        try {
            return m_checkpoint->load();
        } catch (const std::exception& e) {
            std::cerr << "Error loading checkpoint: " << e.what() << std::endl;
            return false;
        }
    }

private:
    openmm::Simulator* m_simulator;
    gpu::Adreno* m_gpu_adreno;
    Checkpoint* m_checkpoint;

    std::string m_gpu_platform;
    std::string m_gpu_vendor;
};

} // namespace fah::openmm
