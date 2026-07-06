#pragma once

#include <chrono>
#include <map>
#include <string>
#include <vector>

// C++ port of the connectors-repo ArtefactSessionLog: per-run offline
// diagnostics for the 4.0 artefact pipeline. Each run writes a timestamped,
// never-overwritten file pair under %TEMP%\Speckle\sessions\:
//   {yyyyMMdd-HHmmss}-Archicad-send-{versionId}.ndjson   (event stream)
//   {yyyyMMdd-HHmmss}-Archicad-send-{versionId}.summary.txt
// Best-effort by design — logging must never break the send.
class ArtefactSessionLog
{
public:
    ArtefactSessionLog(const std::string& connector, const std::string& projectId, const std::string& versionId);
    ~ArtefactSessionLog(); // flushes both files

    void RecordObject(const std::string& appId, const std::string& type, const std::string& status,
                      const std::string& error, double elapsedMs);
    void SetStat(const std::string& name, long long value);

    // Phase timer: BeginPhase, then EndPhase records {phase, elapsedMs}.
    void BeginPhase(const std::string& name);
    void EndPhase();

    void Fail(const std::string& error);

private:
    void AddLine(const std::string& jsonLine);

    std::string _connector;
    std::string _versionId;
    std::string _basePath; // without extension; empty if path resolution failed
    std::vector<std::string> _lines;
    std::map<std::string, long long> _stats;
    std::map<std::string, double> _phaseTimes;
    std::vector<std::pair<std::string, std::string>> _failures; // appId -> error
    int _successCount = 0;
    int _errorCount = 0;
    std::string _currentPhase;
    std::chrono::steady_clock::time_point _phaseStart;
    std::chrono::steady_clock::time_point _sessionStart;
    std::string _fatalError;
};
