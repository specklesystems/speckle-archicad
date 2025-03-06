#pragma once

#include "IBridge.h"
#include "IBrowserAdapter.h"
#include "Binding.h"

class ReceiveBridge : public IBridge {
public:
    ReceiveBridge(IBrowserAdapter* browser);

    ~ReceiveBridge() = default;

private:
    std::unique_ptr<Binding> receiveBinding;

    void OnRunMethod(const RunMethodEventArgs& args);
    void RunMethod(const RunMethodEventArgs& args);

    void Receive(const RunMethodEventArgs& args);
    void AfterGetObjects(const RunMethodEventArgs& args);
};