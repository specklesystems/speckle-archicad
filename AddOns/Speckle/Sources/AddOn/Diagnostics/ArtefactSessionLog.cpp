#include "ArtefactSessionLog.h"

#include <cctype>
#include <ctime>
#include <filesystem>
#include <fstream>
#include <sstream>

#include "json.hpp"

namespace
{
    std::string NowStamp()
    {
        const auto now = std::chrono::system_clock::now();
        const std::time_t t = std::chrono::system_clock::to_time_t(now);
        std::tm tm{};
#ifdef _WIN32
        localtime_s(&tm, &t);
#else
        localtime_r(&t, &tm);
#endif
        char buf[32];
        std::strftime(buf, sizeof(buf), "%Y%m%d-%H%M%S", &tm);
        return buf;
    }

    std::string Sanitize(const std::string& s)
    {
        std::string out;
        for (char c : s)
            out.push_back((std::isalnum(static_cast<unsigned char>(c)) || c == '-' || c == '_') ? c : '_');
        return out.empty() ? "noversion" : out;
    }
}

ArtefactSessionLog::ArtefactSessionLog(const std::string& connector, const std::string& projectId, const std::string& versionId)
    : _connector(connector), _versionId(versionId), _sessionStart(std::chrono::steady_clock::now())
{
    try
    {
        std::filesystem::path dir = std::filesystem::temp_directory_path() / "Speckle" / "sessions";
        std::filesystem::create_directories(dir);
        _basePath = (dir / (NowStamp() + "-" + Sanitize(connector) + "-send-" + Sanitize(versionId))).string();
    }
    catch (...)
    {
        _basePath.clear(); // degrade to no-op
    }

    nlohmann::json start;
    start["record"] = "session_start";
    start["connector"] = connector;
    start["direction"] = "send";
    start["projectId"] = projectId;
    start["versionId"] = versionId;
    AddLine(start.dump());
}

void ArtefactSessionLog::AddLine(const std::string& jsonLine)
{
    try
    {
        _lines.push_back(jsonLine);
    }
    catch (...)
    {
    }
}

void ArtefactSessionLog::RecordObject(const std::string& appId, const std::string& type, const std::string& status,
                                      const std::string& error, double elapsedMs)
{
    if (status == "SUCCESS")
        _successCount++;
    else
    {
        _errorCount++;
        if (_failures.size() < 200)
            _failures.emplace_back(appId, error);
    }

    nlohmann::json rec;
    rec["record"] = "object";
    rec["appId"] = appId;
    rec["type"] = type;
    rec["status"] = status;
    if (!error.empty())
        rec["error"] = error;
    rec["elapsedMs"] = elapsedMs;
    if (!_currentPhase.empty())
        rec["phase"] = _currentPhase;
    AddLine(rec.dump());
}

void ArtefactSessionLog::RecordInstancing(const std::string& appId, const std::string& definitionId, bool reused,
                                          bool transformIsIdentity, double localWorldMaxDelta,
                                          const std::array<double, 3>& worldSample, const std::array<double, 3>& localSample)
{
    _instanceObjects++;
    if (reused)
        _instanceReused++;
    else
        _instanceDefinitions++;
    if (localWorldMaxDelta > 1e-9)
        _instanceLocalDiffers++;
    if (!transformIsIdentity)
        _instanceNonIdentity++;

    nlohmann::json rec;
    rec["record"] = "instance";
    rec["appId"] = appId;
    rec["definitionId"] = definitionId;
    rec["reused"] = reused;
    rec["transformIsIdentity"] = transformIsIdentity;
    rec["localWorldMaxDelta"] = localWorldMaxDelta;
    rec["worldSample"] = { worldSample[0], worldSample[1], worldSample[2] };
    rec["localSample"] = { localSample[0], localSample[1], localSample[2] };
    AddLine(rec.dump());
}

void ArtefactSessionLog::SetStat(const std::string& name, long long value)
{
    _stats[name] = value;
}

void ArtefactSessionLog::BeginPhase(const std::string& name)
{
    _currentPhase = name;
    _phaseStart = std::chrono::steady_clock::now();
}

void ArtefactSessionLog::EndPhase()
{
    if (_currentPhase.empty())
        return;
    const double ms = std::chrono::duration<double, std::milli>(std::chrono::steady_clock::now() - _phaseStart).count();
    _phaseTimes[_currentPhase] = ms;

    nlohmann::json rec;
    rec["record"] = "phase";
    rec["name"] = _currentPhase;
    rec["elapsedMs"] = ms;
    AddLine(rec.dump());
    _currentPhase.clear();
}

void ArtefactSessionLog::Fail(const std::string& error)
{
    _fatalError = error;
    nlohmann::json rec;
    rec["record"] = "session_error";
    rec["error"] = error;
    AddLine(rec.dump());
}

ArtefactSessionLog::~ArtefactSessionLog()
{
    try
    {
        const double totalMs = std::chrono::duration<double, std::milli>(std::chrono::steady_clock::now() - _sessionStart).count();

        nlohmann::json end;
        end["record"] = "session_end";
        end["totalElapsedMs"] = totalMs;
        end["success"] = _successCount;
        end["error"] = _errorCount;
        for (const auto& kv : _stats)
            end["stats"][kv.first] = kv.second;
        AddLine(end.dump());

        if (_basePath.empty())
            return;

        {
            std::ofstream ndjson(_basePath + ".ndjson", std::ios::binary);
            for (const auto& line : _lines)
                ndjson << line << "\n";
        }

        std::ostringstream summary;
        summary << "Speckle artefact session — " << _connector << " send — version " << _versionId << "\n";
        summary << "total elapsed: " << totalMs << " ms\n";
        summary << "objects: " << _successCount << " ok, " << _errorCount << " failed\n";
        if (!_fatalError.empty())
            summary << "FATAL: " << _fatalError << "\n";
        summary << "\nphases:\n";
        for (const auto& kv : _phaseTimes)
            summary << "  " << kv.first << ": " << kv.second << " ms\n";
        summary << "\nstats:\n";
        for (const auto& kv : _stats)
            summary << "  " << kv.first << ": " << kv.second << "\n";

        if (_instanceObjects > 0)
        {
            summary << "\ninstancing (object / GDL library parts):\n";
            summary << "  object instances: " << _instanceObjects << "\n";
            summary << "  unique definitions: " << _instanceDefinitions << "\n";
            summary << "  reused placements: " << _instanceReused << "\n";
            summary << "  ElemLocal != World: " << _instanceLocalDiffers << " of " << _instanceObjects << "\n";
            summary << "  non-identity transform: " << _instanceNonIdentity << " of " << _instanceObjects << "\n";
            summary << "  => ElemLocal is "
                    << (_instanceLocalDiffers > 0 ? "DISTINCT from World for objects (instancing viable)"
                                                  : "identical to World for every object (instancing NOT viable)")
                    << "\n";
        }

        if (!_failures.empty())
        {
            summary << "\nfailed objects (max 200):\n";
            for (const auto& f : _failures)
                summary << "  " << f.first << ": " << f.second << "\n";
        }

        std::ofstream summaryFile(_basePath + ".summary.txt", std::ios::binary);
        summaryFile << summary.str();
    }
    catch (...)
    {
        // Diagnostics must never throw during unwind.
    }
}
