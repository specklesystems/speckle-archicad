#pragma once

#include "IBridge.h"
#include "IBrowserAdapter.h"
#include "Binding.h"

#ifdef __APPLE__
#include <atomic>
#include <cstdint>
#include <memory>
#include <thread>
#endif

class AccountBridge : public IBridge {
public:
    AccountBridge(IBrowserAdapter* browser);

    ~AccountBridge();

private:
#ifdef __APPLE__
    std::shared_ptr<std::atomic_bool> lifetime =
        std::make_shared<std::atomic_bool>(true);
#endif
    std::unique_ptr<Binding> accountsBinding;
#ifdef __APPLE__
    std::jthread authenticationThread;
    std::uint64_t authenticationGeneration = 0;
#endif

    void RunMethod(const RunMethodEventArgs& args);

    void GetAccounts(const RunMethodEventArgs& args);
    void AddAccount(const RunMethodEventArgs& args);
    void RemoveAccount(const RunMethodEventArgs& args);

#ifdef __APPLE__
    void AuthenticateAccount(const RunMethodEventArgs& args);
    void CompleteAuthentication(
        const std::string& methodId,
        nlohmann::json account,
        const std::string& error);
    static void CompleteAuthenticationOnMainQueue(void* context);
#endif
};
