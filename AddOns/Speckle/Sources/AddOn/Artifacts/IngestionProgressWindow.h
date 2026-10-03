#pragma once

#include "IProcessWindow.h"
#include "IngestionHeartbeat.h"

class IngestionProgressWindow final : public IProcessWindow
{
public:
    IngestionProgressWindow(IProcessWindow& window, IngestionHeartbeat& heartbeat)
        : window(window), heartbeat(heartbeat) {}

    void Init(const std::string& title, int count) override { window.Init(title, count); }
    void SetNextProcessPhase(const std::string& title, int count) override
    {
        heartbeat.CheckCancellation();
        heartbeat.SetMessage(title);
        window.SetNextProcessPhase(title, count);
    }
    void SetProcessValue(int value) override
    {
        heartbeat.CheckCancellation();
        window.SetProcessValue(value);
    }
    bool IsProcessCanceled() override
    {
        heartbeat.CheckCancellation();
        return window.IsProcessCanceled();
    }
    void Close() override { window.Close(); }

private:
    IProcessWindow& window;
    IngestionHeartbeat& heartbeat;
};
