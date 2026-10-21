#pragma once

#include "json.hpp"
#include <string>

// Machine-wide connector configuration: env var > HKLM > HKCU > default,
// the same keys and precedence as the .NET connectors' GlobalConfigResolver.
class GlobalConfig
{
public:
    static std::string GetDuiUrl();
    static std::string GetDefaultSpeckleServerUrl();
    static bool IsUpdateNotificationDisabled();
    static nlohmann::json ToJson();
};
