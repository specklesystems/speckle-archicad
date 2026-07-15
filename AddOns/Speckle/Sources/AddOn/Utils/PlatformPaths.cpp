#include "PlatformPaths.h"

#include <cstdlib>
#include <stdexcept>

#ifdef _WIN32
#include <shlobj.h>
#include <windows.h>
#endif

namespace PlatformPaths
{
    std::filesystem::path GetSpeckleApplicationDataDirectory()
    {
#ifdef _WIN32
        PWSTR appDataPath = nullptr;
        const HRESULT result = SHGetKnownFolderPath(FOLDERID_RoamingAppData, 0, nullptr, &appDataPath);
        if (FAILED(result) || appDataPath == nullptr)
            throw std::runtime_error("Failed to resolve the Windows application-data directory");

        const std::filesystem::path directory = std::filesystem::path(appDataPath) / L"Speckle";
        CoTaskMemFree(appDataPath);
#elif defined(__APPLE__)
        const char* home = std::getenv("HOME");
        if (home == nullptr || *home == '\0')
            throw std::runtime_error("HOME is not set");

        const std::filesystem::path directory =
            std::filesystem::path(home) / "Library" / "Application Support" / "Speckle";
#else
        const char* configHome = std::getenv("XDG_CONFIG_HOME");
        const char* home = std::getenv("HOME");
        const std::filesystem::path directory = configHome != nullptr && *configHome != '\0'
            ? std::filesystem::path(configHome) / "Speckle"
            : std::filesystem::path(home != nullptr ? home : "") / ".config" / "Speckle";
#endif

        std::filesystem::create_directories(directory);
        return directory;
    }

    std::string ToUtf8(const std::filesystem::path& path)
    {
#ifdef _WIN32
        const std::wstring wide = path.native();
        if (wide.empty())
            return {};

        const int size = WideCharToMultiByte(
            CP_UTF8, 0, wide.data(), static_cast<int>(wide.size()), nullptr, 0, nullptr, nullptr);
        if (size <= 0)
            throw std::runtime_error("Failed to convert a filesystem path to UTF-8");

        std::string utf8(static_cast<std::size_t>(size), '\0');
        WideCharToMultiByte(
            CP_UTF8, 0, wide.data(), static_cast<int>(wide.size()), utf8.data(), size, nullptr, nullptr);
        return utf8;
#else
        return path.string();
#endif
    }
}
