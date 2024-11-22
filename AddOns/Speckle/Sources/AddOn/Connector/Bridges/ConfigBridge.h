#pragma once

#include "IBrowserAdapter.h"
#include "Binding.h"

class ConfigBridge {
public:
    ConfigBridge(IBrowserAdapter* browser);

    ~ConfigBridge() = default;

private:
    std::unique_ptr<Binding> configBinding;

    void Init(IBrowserAdapter* browser);
    void OnRunMethod(const RunMethodEventArgs& args);

    void GetConfig(const RunMethodEventArgs& args);
    void GetIsDevMode(const RunMethodEventArgs& args);
    void UpdateConfig(const RunMethodEventArgs& args);
};
