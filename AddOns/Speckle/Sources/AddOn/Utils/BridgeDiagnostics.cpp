#include "BridgeDiagnostics.h"

#include "PlatformPaths.h"

#include <filesystem>
#include <fstream>
#include <mutex>

namespace
{
    std::mutex diagnosticsMutex;

    std::filesystem::path GetDiagnosticsPath()
    {
        return PlatformPaths::GetSpeckleApplicationDataDirectory()
            / "Archicad" / "bridge-debug.log";
    }
}

void BridgeDiagnostics::Reset()
{
    try
    {
        std::lock_guard<std::mutex> lock(diagnosticsMutex);
        const auto path = GetDiagnosticsPath();
        std::filesystem::create_directories(path.parent_path());
        std::ofstream(path, std::ios::trunc) << "bridge-diagnostics-start\n";
    }
    catch (...)
    {
        // Diagnostics must never prevent the connector from loading.
    }
}

void BridgeDiagnostics::Write(const std::string& event)
{
    try
    {
        std::lock_guard<std::mutex> lock(diagnosticsMutex);
        std::ofstream(GetDiagnosticsPath(), std::ios::app) << event << '\n';
    }
    catch (...)
    {
        // Diagnostics must never affect connector behavior.
    }
}
