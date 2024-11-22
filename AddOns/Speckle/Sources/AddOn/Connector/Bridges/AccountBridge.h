#pragma once

#include "IBrowserAdapter.h"
#include "Binding.h"

class AccountBridge {
public:
    AccountBridge(IBrowserAdapter* browser);

    ~AccountBridge() = default;

private:
    std::unique_ptr<Binding> accountsBinding;
    
    void Init(IBrowserAdapter* browser);
    void OnRunMethod(const RunMethodEventArgs& args);

    void GetAccounts(const RunMethodEventArgs& args);
};
