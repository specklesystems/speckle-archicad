#pragma once

#include "Event.h"
#include "RunMethodEventArgs.h"
#include "json.hpp"
#include "IBrowserAdapter.h"

class Binding {
public:
    Event<const RunMethodEventArgs&> RunMethodRequested;

private:
    std::string _name;
    std::vector<std::string> _methodNames;

    // this adapter will provide an interface for Bindings to register their JSObjects, and function names
    // without needing to include GS dependencies in the Binding class
    IBrowserAdapter* _browserAdapter;

    std::map<std::string, std::unique_ptr<nlohmann::json>> results;

public:
    Binding() = default;
    Binding(const std::string& name, const std::vector<std::string>& methodNames, IBrowserAdapter* browserAdapter);
    ~Binding() = default;

    std::string GetName() const;
    std::vector<std::string> GetMethodNames() const;

    std::unique_ptr <nlohmann::json> GetResult(const std::string& key);
    void SetResult(const std::string& key, nlohmann::json value);
    void CacheResult(const std::string& key, std::unique_ptr<nlohmann::json>);
    void ResponseReady(const std::string methodId);
    void EmitResponseReady(const std::string methodName, const std::string methodId);
    void ClearResult(const std::string& key);
};
