#pragma once

#include "Event.h"
#include "RunMethodEventArgs.h"
#include "json.hpp"
#include "IBridge.h"
#include "IBrowserAdapter.h"
#include "ToastNotification.h"


class Binding 
{
private:
    std::string _name;
    std::vector<std::string> _methodNames;

    // this adapter will provide an interface for Bindings to register their JSObjects, and function names
    // without needing to include GS dependencies to DG::Browser in the Binding class
    IBrowserAdapter* _browserAdapter;
    IBridge* _bridge;

    std::map<std::string, nlohmann::json> results;

public:
    Binding() = default;
    Binding(const std::string& name, const std::vector<std::string>& methodNames, IBrowserAdapter* browserAdapter, IBridge* bridge);
    ~Binding() = default;

    std::string GetName() const;
    std::vector<std::string> GetMethodNames() const;

    nlohmann::json GetResult(const std::string& methodId);
    void SetResult(const std::string& methodId, const nlohmann::json& data);
    void Send(const std::string& methodName, const nlohmann::json& data);
    void SendByBrowser(const std::string& sendMethodId, const nlohmann::json& data);
    void SendBatchViaBrowser(const std::string& sendMethodId, const nlohmann::json& data);
    void CreateVersionViaBrowser(const std::string& sendMethodId, const nlohmann::json& data);

    void CacheResult(const std::string& methodId, const nlohmann::json& result);
    void ResponseReady(const std::string methodId);
    void EmitResponseReady(const std::string methodName, const std::string methodId);
    void Emit(const std::string eventName);
    void ClearResult(const std::string& methodId);

    void SetToastNotification(const ToastNotification& toast);

    void RunMethod(const RunMethodEventArgs& args);
};
