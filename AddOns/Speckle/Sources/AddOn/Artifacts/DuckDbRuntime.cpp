#include "DuckDbRuntime.h"

#include <filesystem>
#include <stdexcept>
#include <string>

#ifdef _WIN32
#define WIN32_LEAN_AND_MEAN
#define NOMINMAX
#include <windows.h>
#endif

namespace DuckDbRuntime
{
#ifdef _WIN32
    void EnsureLoaded()
    {
        static bool loaded = false;
        if (loaded)
            return;

        HMODULE self = nullptr;
        if (!GetModuleHandleExW(
                GET_MODULE_HANDLE_EX_FLAG_FROM_ADDRESS | GET_MODULE_HANDLE_EX_FLAG_UNCHANGED_REFCOUNT,
                reinterpret_cast<LPCWSTR>(&EnsureLoaded),
                &self))
        {
            throw std::runtime_error("Could not resolve the add-on module handle");
        }

        wchar_t path[MAX_PATH];
        if (GetModuleFileNameW(self, path, MAX_PATH) == 0)
        {
            throw std::runtime_error("Could not resolve the add-on module path");
        }

        std::filesystem::path dllPath = std::filesystem::path(path).parent_path() / L"duckdb.dll";
        if (LoadLibraryW(dllPath.c_str()) == nullptr)
        {
            throw std::runtime_error(
                "Could not load duckdb.dll from the add-on folder (" + dllPath.string() +
                ") — is it deployed next to Speckle.apx?");
        }
        loaded = true;
    }
#else
    void EnsureLoaded() {}
#endif
}
