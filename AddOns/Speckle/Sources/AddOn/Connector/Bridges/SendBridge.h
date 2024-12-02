#pragma once

#include "IBrowserAdapter.h"
#include "Binding.h"

class SendBridge {
public:
    SendBridge(IBrowserAdapter* browser);

    ~SendBridge() = default;

private:
    std::unique_ptr<Binding> sendBinding;

    void OnRunMethod(const RunMethodEventArgs& args);
    void RunMethod(const RunMethodEventArgs& args);

    void GetSendFilters(const RunMethodEventArgs& args);
    void GetSendSettings(const RunMethodEventArgs& args);
    void Send(const RunMethodEventArgs& args);
};
