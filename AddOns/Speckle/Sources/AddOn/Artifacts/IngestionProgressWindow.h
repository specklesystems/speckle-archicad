#pragma once

#include <chrono>
#include <string>

#include "IProcessWindow.h"

class ArtifactUploader;

// The C++ counterpart of the SDK's AggregateProgress(IngestionProgressManager, uiProgress):
// forwards every call to the host process window and reports the same phase + fraction to
// the ingestion, throttled to one update per interval.
class IngestionProgressWindow : public IProcessWindow
{
public:
    IngestionProgressWindow(
        IProcessWindow& inner,
        ArtifactUploader& uploader,
        const std::string& ingestionId,
        std::chrono::steady_clock::duration updateInterval);

    void Init(const std::string& title, int phaseCount) override;
    void SetNextProcessPhase(const std::string& title, int phaseCount) override;
    void SetProcessValue(int value) override;
    bool IsProcessCanceled() override;
    void Close() override;

private:
    void Report(int value);

    IProcessWindow& _inner;
    ArtifactUploader& _uploader;
    std::string _ingestionId;
    std::chrono::steady_clock::duration _updateInterval;
    std::chrono::steady_clock::time_point _lastUpdatedAt;
    std::string _phaseTitle;
    int _phaseMax = 0;
};
