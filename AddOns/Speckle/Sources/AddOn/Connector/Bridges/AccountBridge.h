#pragma once

#include "IBridge.h"
#include "IBrowserAdapter.h"
#include "Binding.h"

class AccountBridge : public IBridge {
public:
    AccountBridge(IBrowserAdapter* browser);

    ~AccountBridge() = default;

private:
    std::unique_ptr<Binding> accountsBinding;
    
    void OnRunMethod(const RunMethodEventArgs& args);
    void RunMethod(const RunMethodEventArgs& args);

    void GetAccounts(const RunMethodEventArgs& args);
    void RemoveAccount(const RunMethodEventArgs& args);
};
