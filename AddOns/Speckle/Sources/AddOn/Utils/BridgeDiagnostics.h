#pragma once

#include <string>

namespace BridgeDiagnostics
{
    void Reset();
    void Write(const std::string& event);
}
