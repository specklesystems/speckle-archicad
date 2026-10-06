#include "IngestionProgressWindow.h"

#include <algorithm>
#include <optional>

#include "ArtifactUploader.h"

IngestionProgressWindow::IngestionProgressWindow(
    IProcessWindow& inner,
    ArtifactUploader& uploader,
    const std::string& ingestionId,
    std::chrono::steady_clock::duration updateInterval)
    : _inner(inner),
      _uploader(uploader),
      _ingestionId(ingestionId),
      _updateInterval(updateInterval),
      _lastUpdatedAt(std::chrono::steady_clock::now())
{
}

void IngestionProgressWindow::Init(const std::string& title, int phaseCount)
{
    _inner.Init(title, phaseCount);
}

void IngestionProgressWindow::SetNextProcessPhase(const std::string& title, int phaseCount)
{
    _inner.SetNextProcessPhase(title, phaseCount);
    _phaseTitle = title;
    _phaseMax = phaseCount;
    Report(0);
}

void IngestionProgressWindow::SetProcessValue(int value)
{
    _inner.SetProcessValue(value);
    Report(value);
}

bool IngestionProgressWindow::IsProcessCanceled()
{
    return _inner.IsProcessCanceled();
}

void IngestionProgressWindow::Close()
{
    _inner.Close();
}

void IngestionProgressWindow::Report(int value)
{
    if (std::chrono::steady_clock::now() - _lastUpdatedAt < _updateInterval)
        return;

    std::optional<double> progress;
    if (_phaseMax > 0)
        progress = std::clamp(static_cast<double>(value) / _phaseMax, 0.0, 1.0);
    _uploader.UpdateProgress(_ingestionId, _phaseTitle, progress);

    // Stamped after the synchronous request: a slow server then stretches the gap
    // between heartbeats instead of the send spending its time on them.
    _lastUpdatedAt = std::chrono::steady_clock::now();
}
