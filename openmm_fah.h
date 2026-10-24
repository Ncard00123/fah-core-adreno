#include <openmm/PlatformData.h>
#include <openmm/PlatformUtils.h>
#include <openmm/PlatformApplicationData.h>
#include <openmm/PlatformData.h>
#include <openmm/PlatformUtils.h>
#include <openmm/PlatformApplicationData.h>

#include <openmm/Context.h>
#include <openmm/Force.h>
#include <openmm/PlatformData.h>
#include <openmm/PlatformUtils.h>
#include <openmm/PlatformApplication.h>
#include <openmm/PlatformApplicationData.h>

#include <openmm/PlatformData.h>
#include <openmm/PlatformUtils.h>
#include <openmm/PlatformApplicationData.h>

#include <openmm/Context.h>
#include <openmm/Force.h>
#include <openmm/PlatformData.h>
#include <openmm/PlatformUtils.h>
#include <openmm/PlatformApplication.h>
#include <openmm/PlatformApplicationData.h>

#include <openmm/PlatformData.h>
#include <openmm/PlatformUtils.h>
#include <openmm/PlatformApplicationData.h>

#include <openmm/Context.h>
#include <openmm/Force.h>
#include <openmm/PlatformData.h>
#include <openmm/PlatformUtils.h>
#include <openmm/PlatformApplication.h>
#include <openmm/PlatformApplicationData.h>

#include <openmm/PlatformData.h>
#include <openmm/PlatformUtils.h>
#include <openmm/PlatformApplicationData.h>

#include <openmm/Context.h>
#include <openmm/Force.h>
#include <openmm/PlatformData.h>
#include <openmm/PlatformUtils.h>
#include <openmm/PlatformApplication.h>
#include <openmm/PlatformApplicationData.h>

#include <openmm/PlatformData.h>
#include <openmm/PlatformUtils.h>
#include <openmm/PlatformApplicationData.h>

#include <openmm/Context.h>
#include <openmm/Force.h>
#include <openmm/PlatformData.h>
#include <openmm/PlatformUtils.h>
#include <openmm/PlatformApplication.h>
#include <openmm/PlatformApplicationData.h>

#include <openmm/PlatformData.h>
#include <openmm/PlatformUtils.h>
#include <openmm/PlatformApplicationData.h>

#include <openmm/Context.h>
#include <openmm/Force.h>
#include <openmm/PlatformData.h>
#include <openmm/PlatformUtils.h>
#include <openmm/PlatformApplication.h>
#include <openmm/PlatformApplicationData.h>

#include <openmm/PlatformData.h>
#include <openmm/PlatformUtils.h>
#include <openmm/PlatformApplicationData.h>

#include <openmm/Context.h>
#include <openmm/Force.h>
#include <openmm/PlatformData.h>
#include <openmm/PlatformUtils.h>
#include <openmm/PlatformApplication.h>
#include <openmm/PlatformApplicationData.h>

#include <openmm/PlatformData.h>
#include <openmm/PlatformUtils.h>
#include <openmm/PlatformApplicationData.h>

#include <openmm/Context.h>
#include <openmm/Force.h>
#include <openmm/PlatformData.h>
#include <openmm/PlatformUtils.h>
#include <openmm/PlatformApplication.h>
#include <openmm/PlatformApplicationData.h>

#include <openmm/PlatformData.h>
#include <openmm/PlatformUtils.h>
#include <openmm/PlatformApplicationData.h>

#include <openmm/Context.h>
#include <openmm/Force.h>
#include <openmm/PlatformData.h>
#include <openmm/PlatformUtils.h>
#include <openmm/PlatformApplication.h>
#include <openmm/PlatformApplicationData.h>

#include <openmm/PlatformData.h>
#include <openmm/PlatformUtils.h>
#include <openmm/PlatformApplicationData.h>

namespace fah::openmm {

class AdrenoPlatform : public openmm::Platform {
public:
    AdrenoPlatform();
    virtual ~AdrenoPlatform();

    // Inherited from openmm::Platform
    virtual std::string getName() const override;
    virtual std::string getVersion() const override;
    virtual std::string getReleaseDate() const override;

    virtual void initialize() override;
    virtual void finalize() override;

    virtual void setUpContext(
        openmm::Context& context,
        openmm::PlatformData& platformData,
        const std::vector<std::string>& commandLineArgs) override;

    virtual void executeContext(
        openmm::Context& context,
        openmm::PlatformData& platformData,
        const std::vector<std::string>& commandLineArgs) override;

    virtual void finalizeContext(
        openmm::Context& context,
        openmm::PlatformData& platformData) override;

    virtual void setUpForce(
        openmm::Force& force,
        openmm::PlatformData& platformData,
        const std::string& forceName) override;

    virtual void finalizeForce(
        openmm::Force& force,
        openmm::PlatformData& platformData) override;

    // GPU-specific methods
    virtual bool hasGpu() const override;
    virtual bool hasCuda() const override;
    virtual bool hasOpenCL() const override;
    virtual bool hasOpenMP() const override;
    virtual bool hasAMDGPU() const override;
    virtual bool hasIntelGPU() const override;

    // Checkpoint support
    virtual void writeCheckpoint(
        openmm::Context& context,
        openmm::PlatformData& platformData,
        openmm::FileCheckpoint& checkpoint) override;

    virtual void readCheckpoint(
        openmm::Context& context,
        openmm::PlatformData& platformData,
        openmm::FileCheckpoint& checkpoint) override;

    // OpenCL context management
    virtual cl::Context& getOpenCLContext() override;
    virtual void setOpenCLContext(cl::Context& context) override;

private:
    // OpenCL context and command queue
    cl::Context m_opencl_context;
    cl::CommandQueue m_opencl_queue;

    // GPU information
    std::string m_gpu_vendor;
    std::string m_gpu_name;
    std::string m_gpu_version;

    // Platform data
    openmm::PlatformData m_platform_data;

    // Checkpoint handling
    openmm::FileCheckpoint m_checkpoint;

    // Initialize Adreno-specific OpenCL
    void initializeAdrenoOpenCL();
    void initializeAdrenoVulkan();
    void initializeAdrenoDirectML();

    // Parse FAH command line arguments
    void parseFahArgs(const std::vector<std::string>& args);
};

} // namespace fah::openmm
