#pragma once

#include <array>
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

    // Records one object emitted as an instance. Aggregated into the summary so a send can
    // prove — without a debugger — that ElemLocal geometry differs from World for objects
    // (localWorldMaxDelta > 0 / non-identity transform) and that shared definitions dedup
    // (unique definitions < object instances).
    void RecordInstancing(const std::string& appId, const std::string& definitionId, bool reused,
                          bool transformIsIdentity, double localWorldMaxDelta,
                          const std::array<double, 3>& worldSample, const std::array<double, 3>& localSample);

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

    // instancing verification aggregates
    int _instanceObjects = 0;      // objects emitted as instances
    int _instanceDefinitions = 0;  // unique definitions (first sighting of a definitionId)
    int _instanceReused = 0;       // placements that reused an existing definition
    int _instanceLocalDiffers = 0; // objects where sampled ElemLocal != World
    int _instanceNonIdentity = 0;  // objects with a non-identity local->world transform
    std::string _currentPhase;
    std::chrono::steady_clock::time_point _phaseStart;
    std::chrono::steady_clock::time_point _sessionStart;
    std::string _fatalError;
};
