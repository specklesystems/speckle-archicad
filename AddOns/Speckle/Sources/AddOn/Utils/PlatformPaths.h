#pragma once

#include <filesystem>
#include <string>

namespace PlatformPaths
{
    std::filesystem::path GetSpeckleApplicationDataDirectory();
    std::string ToUtf8(const std::filesystem::path& path);
}
