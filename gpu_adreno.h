#pragma once
#include <string>

namespace fah::gpu {
    class Adreno {
    public:
        Adreno();
        bool detect();
        std::string get_gpu_id() const;
        bool is_available() const;
        void update_gpu_utilization(int utilization);
        int get_gpu_temperature() const;
        bool is_throttling_active() const;

    private:
        std::string m_gpu_id;
        bool m_is_available;
        int m_gpu_utilization;
        int m_gpu_temperature;
        bool m_throttling_active;
        int m_max_temperature;
    };
}