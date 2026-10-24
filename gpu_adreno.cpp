#cpp
#include <windows.h>
#include <iphlpapi.h>
#include <comdef.h>
#include <Wbemidl.h>
#include <clocale>
#include <string>
#include <vector>
#include <iostream>
#include <iomanip>
#include <sstream>

#pragma comment(lib, "iphlpapi.lib")
#pragma comment(lib, "wbemuuid.lib")
#pragma comment(lib, "ole32.lib")
#pragma comment(lib, "oleaut32.lib")

namespace fah::gpu {
    class Adreno {
    public:
        Adreno() : m_gpu_id("unknown"), m_is_available(false), m_gpu_utilization(0),
                  m_gpu_temperature(0), m_throttling_active(false), m_max_temperature(90) {}

        bool detect() {
            std::vector<std::string> wmi_classes = { "Win32_VideoController", "Win32_PnPEntity" };
            
            HRESULT hr = CoInitializeEx(0, COINIT_MULTITHREADED);
            if (FAILED(hr) && hr != RPC_E_CHANGED_MODE) {
                return false;
            }

            hr = CoInitializeSecurity(
                NULL, -1, NULL, NULL, 
                RPC_C_AUTHN_LEVEL_DEFAULT, RPC_C_IMP_LEVEL_IMPERSONATE,
                NULL, EOAC_NONE, NULL
            );

            for (const auto& wmi_class : wmi_classes) {
                IWbemLocator* locator = nullptr;
                IWbemServices* services = nullptr;

                hr = CoCreateInstance(
                    CLSID_WbemLocator, 0, CLSCTX_INPROC_SERVER, IID_IWbemLocator, (LPVOID*)&locator
                );

                if (SUCCEEDED(hr)) {
                    hr = locator->ConnectServer(
                        _bstr_t(L"ROOT\\CIMV2"), NULL, NULL, 0, NULL, 0, 0, &services
                    );

                    if (SUCCEEDED(hr)) {
                        IEnumWbemClassObject* enum_classes = nullptr;
                        hr = services->ExecQuery(
                            bstr_t("WQL"), bstr_t(("SELECT Name FROM " + wmi_class).c_str()), 
                            WBEM_FLAG_FORWARD_ONLY | WBEM_FLAG_RETURN_IMMEDIATELY, NULL, &enum_classes
                        );

                        if (SUCCEEDED(hr) && enum_classes != nullptr) {
                            IWbemClassObject* pclsObj = nullptr;
                            ULONG uReturn = 0;
                            while (enum_classes->Next(WBEM_INFINITE, 1, &pclsObj, &uReturn) == 0) {
                                if (uReturn == 0) break;

                                VARIANT vtProp;
                                hr = pclsObj->Get(L"Name", 0, &vtProp, 0, 0);
                                if (SUCCEEDED(hr) && vtProp.vt == VT_BSTR && vtProp.bstrVal != nullptr) {
                                    std::wstring ws(vtProp.bstrVal);
                                    std::string name(ws.begin(), ws.end());
                                    
                                    if (name.find("Adreno") != std::string::npos) {
                                        m_gpu_id = name;
                                        m_is_available = true;
                                        std::cout << "[GPU] Detected Adreno GPU: " << name << std::endl;
                                        VariantClear(&vtProp);
                                        pclsObj->Release();
                                        break;
                                    }
                                }
                                VariantClear(&vtProp);
                                pclsObj->Release();
                            }
                            enum_classes->Release();
                        }
                        services->Release();
                    }
                    locator->Release();
                }

                if (m_is_available) break;
            }

            CoUninitialize();
            return m_is_available;
        }

        std::string get_gpu_id() const { return m_gpu_id; }
        bool is_available() const { return m_is_available; }

        void update_gpu_utilization(int utilization) {
            m_gpu_utilization = utilization;
        }

        int get_gpu_temperature() const { return m_gpu_temperature; }
        bool is_throttling_active() const { return m_throttling_active; }

    private:
        std::string m_gpu_id;
        bool m_is_available;
        int m_gpu_utilization;
        int m_gpu_temperature;
        bool m_throttling_active;
        int m_max_temperature;
    };
}