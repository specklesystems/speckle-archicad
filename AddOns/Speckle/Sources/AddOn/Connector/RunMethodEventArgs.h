#pragma once

#include <string>
#include "json.hpp"

class Binding;

struct RunMethodEventArgs {
    Binding* eventSource;
    std::string methodName;
    std::string methodId;
    std::vector<nlohmann::json> data;

    // Constructor to initialize all members
    RunMethodEventArgs(Binding* eventSource, const std::string& methodName, const std::string& methodId, const std::vector<nlohmann::json>& data)
        : eventSource(eventSource), methodName(methodName), methodId(methodId), data(data) {}
};
