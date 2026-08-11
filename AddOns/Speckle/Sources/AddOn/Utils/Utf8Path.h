#pragma once

#include <filesystem>
#include <string>

// UTF-8 <-> std::filesystem::path bridging. All file paths the add-on passes
// around as std::string are UTF-8; on Windows the narrow CRT/iostream openers
// interpret narrow strings in the ANSI codepage instead, so every filesystem
// touch point must round-trip through these helpers (%TEMP%/%APPDATA% may
// contain a non-ASCII user name).
namespace Utf8Path
{
    inline std::filesystem::path FromUtf8(const std::string& utf8)
    {
        return std::filesystem::path(std::u8string(utf8.begin(), utf8.end()));
    }

    inline std::string ToUtf8(const std::filesystem::path& path)
    {
        const std::u8string u8 = path.u8string();
        return std::string(u8.begin(), u8.end());
    }
}
