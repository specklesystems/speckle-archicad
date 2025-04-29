#pragma once

#include "IBridge.h"
#include "IBrowserAdapter.h"
#include "Binding.h"
#include "SendConversionResult.h"

class SendBridge : public IBridge {
public:
    SendBridge(IBrowserAdapter* browser);

    ~SendBridge() = default;

private:
    std::unique_ptr<Binding> sendBinding;
    std::vector<SendConversionResult> conversionResultCache;
    void RunMethod(const RunMethodEventArgs& args);

    void GetSendFilters(const RunMethodEventArgs& args);
    void GetSendSettings(const RunMethodEventArgs& args);
    void Send(const RunMethodEventArgs& args);
    void AfterSendObjects(const RunMethodEventArgs& args);
};
