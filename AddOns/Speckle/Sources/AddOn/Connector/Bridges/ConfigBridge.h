#pragma once

#include "IBridge.h"
#include "IBrowserAdapter.h"
#include "Binding.h"

class ConfigBridge : public IBridge {
public:
    ConfigBridge(IBrowserAdapter* browser);

    ~ConfigBridge() = default;

private:
    std::unique_ptr<Binding> configBinding;

    void OnRunMethod(const RunMethodEventArgs& args);
    void RunMethod(const RunMethodEventArgs& args);

    void GetConfig(const RunMethodEventArgs& args);
    void GetIsDevMode(const RunMethodEventArgs& args);
    void UpdateConfig(const RunMethodEventArgs& args);
    void OpenUrl(const RunMethodEventArgs& args);
    void GetUserSelectedAccountId(const RunMethodEventArgs& args);
    void SetUserSelectedAccountId(const RunMethodEventArgs& args);
};
