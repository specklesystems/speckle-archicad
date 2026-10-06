#pragma once

#include <chrono>
#include <string>

#include "IProcessWindow.h"

class ArtifactUploader;

// Decorates the host process window so the phases it shows also heartbeat the ingestion,
// which the server reaps once it has been idle past its timeout (ENG-10294).
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
