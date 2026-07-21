#include "UrlLauncher.h"

#include <stdexcept>
#include <string>
#include <windows.h>
#include <shellapi.h>

#pragma comment(lib, "shell32.lib")

namespace UrlLauncher
{
    void Open(const std::string& url)
    {
        int wideLen = MultiByteToWideChar(CP_UTF8, 0, url.c_str(), -1, nullptr, 0);
        std::wstring wideUrl(wideLen > 0 ? wideLen - 1 : 0, L'\0');
        if (wideLen > 0)
            MultiByteToWideChar(CP_UTF8, 0, url.c_str(), -1, &wideUrl[0], wideLen);

        HINSTANCE result = ShellExecuteW(nullptr, L"open", wideUrl.c_str(), nullptr, nullptr, SW_SHOWNORMAL);
        // ShellExecute returns a value <= 32 on failure.
        if (reinterpret_cast<INT_PTR>(result) <= 32)
            throw std::runtime_error("Failed to open URL in the default browser.");
    }
}
