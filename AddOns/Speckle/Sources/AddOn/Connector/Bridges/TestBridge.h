#pragma once

#include "IBrowserAdapter.h"
#include "Binding.h"

class TestBridge {
public:
    TestBridge(IBrowserAdapter* browser);

    ~TestBridge() = default;

private:
    std::unique_ptr<Binding> testBinding;

    void Init(IBrowserAdapter* browser);
    void OnRunMethod(const RunMethodEventArgs& args);

    void GetComplexType(const RunMethodEventArgs& args);
    void GoAway(const RunMethodEventArgs& args);
    void SayHi(const RunMethodEventArgs& args);
    void TriggerEvent(const RunMethodEventArgs& args);
};
