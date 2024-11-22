#pragma once

#include <string>

class Binding;

struct RunMethodEventArgs {
    Binding* eventSource;
    std::string methodName;
    std::string methodId;
    std::string args; // TODO: make this a string list

    // Constructor to initialize all members
    RunMethodEventArgs(Binding* eventSource, const std::string& methodName, const std::string& methodId, const std::string& args)
        : eventSource(eventSource), methodName(methodName), methodId(methodId), args(args) {}
};
