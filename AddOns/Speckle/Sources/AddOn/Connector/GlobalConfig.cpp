#include "GlobalConfig.h"
#include "Debug.h"

#include <algorithm>
#include <cctype>
#include <cstdlib>
#include <optional>

#if defined(_WIN32)
#include <windows.h>
#endif

namespace
{
    const char* DUI_URL_KEY = "SPECKLE_DUI_URL";
    const char* DEFAULT_SERVER_URL_KEY = "SPECKLE_DEFAULT_SPECKLE_SERVER_URL";
    const char* UPDATE_NOTIFICATION_DISABLED_KEY = "SPECKLE_IS_UPDATE_NOTIFICATION_DISABLED";
    const char* DEFAULT_DUI_URL = "https://dui.speckle.systems/";
    const char* DEFAULT_SERVER_URL = "https://app.speckle.systems";

    std::optional<std::string> Present(const std::string& value)
    {
        auto notSpace = [](unsigned char c) { return !std::isspace(c); };
        auto begin = std::find_if(value.begin(), value.end(), notSpace);
        auto end = std::find_if(value.rbegin(), value.rend(), notSpace).base();
        if (begin >= end)
            return std::nullopt;
        return std::string(begin, end);
    }

#if defined(_WIN32)
    std::string WideStringToString(const std::wstring& wideString)
    {
        int sizeNeeded = WideCharToMultiByte(CP_UTF8, 0, wideString.c_str(), -1, nullptr, 0, nullptr, nullptr);
        if (sizeNeeded <= 1)
            return {};
        std::string narrowString(sizeNeeded - 1, 0);
        WideCharToMultiByte(CP_UTF8, 0, wideString.c_str(), -1, &narrowString[0], sizeNeeded, nullptr, nullptr);
        return narrowString;
    }

    std::optional<std::string> ReadRegistry(HKEY root, const std::string& key)
    {
        std::wstring keyW(key.begin(), key.end());
        wchar_t buffer[2048];
        DWORD size = sizeof(buffer);
        LSTATUS status = RegGetValueW(root, L"Software\\Speckle\\Connector Config\\Global",
            keyW.c_str(), RRF_RT_REG_SZ, nullptr, buffer, &size);
        if (status != ERROR_SUCCESS)
            return std::nullopt;
        return Present(WideStringToString(buffer));
    }
#endif

    std::optional<std::string> GetConfigValue(const std::string& key)
    {
        if (const char* env = std::getenv(key.c_str()))
            if (auto value = Present(env))
                return value;
#if defined(_WIN32)
        if (auto value = ReadRegistry(HKEY_LOCAL_MACHINE, key))
            return value;
        if (auto value = ReadRegistry(HKEY_CURRENT_USER, key))
            return value;
#endif
        return std::nullopt;
    }

    void Warn(const std::string& key, const std::string& value)
    {
        std::string message = "Failed to parse " + key + " '" + value + "'\n";
        Debug::Print(message);
    }

    bool IsHttpUrl(const std::string& value)
    {
        if (value.find_first_of(" \t\r\n") != std::string::npos)
            return false;
        for (const std::string scheme : { "https://", "http://" })
            if (value.size() > scheme.size() && value.compare(0, scheme.size(), scheme) == 0)
                return true;
        return false;
    }

    std::string UrlValue(const std::string& key, const std::string& fallback)
    {
        auto value = GetConfigValue(key);
        if (!value)
            return fallback;
        if (IsHttpUrl(*value))
            return *value;
        Warn(key, *value);
        return fallback;
    }

    bool BoolValue(const std::string& key, bool fallback)
    {
        auto value = GetConfigValue(key);
        if (!value)
            return fallback;
        std::string lower = *value;
        std::transform(lower.begin(), lower.end(), lower.begin(),
            [](unsigned char c) { return static_cast<char>(std::tolower(c)); });
        if (lower == "true")
            return true;
        if (lower == "false")
            return false;
        Warn(key, *value);
        return fallback;
    }
}

std::string GlobalConfig::GetDuiUrl()
{
    return UrlValue(DUI_URL_KEY, DEFAULT_DUI_URL);
}

std::string GlobalConfig::GetDefaultSpeckleServerUrl()
{
    return UrlValue(DEFAULT_SERVER_URL_KEY, DEFAULT_SERVER_URL);
}

bool GlobalConfig::IsUpdateNotificationDisabled()
{
    return BoolValue(UPDATE_NOTIFICATION_DISABLED_KEY, false);
}

nlohmann::json GlobalConfig::ToJson()
{
    return {
        { "isUpdateNotificationDisabled", IsUpdateNotificationDisabled() },
        { "defaultSpeckleServerUrl", GetDefaultSpeckleServerUrl() },
        { "duiUrl", GetDuiUrl() }
    };
}
